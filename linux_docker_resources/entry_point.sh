#!/bin/sh

# This file fixes the permissions of the home directory so that it matches the host user's ID.
# It also enables multicast and changes directories before executing the input from docker run.

# Adapted from: http://chapeau.freevariable.com/2014/08/docker-uid.html

export ORIGPASSWD=$(cat /etc/passwd | grep rosbuild)
export ORIG_UID=$(echo $ORIGPASSWD | cut -f3 -d:)
export ORIG_GID=$(echo $ORIGPASSWD | cut -f4 -d:)

export UID=${UID:=$ORIG_UID}
export GID=${GID:=$ORIG_GID}

ORIG_HOME=$(echo $ORIGPASSWD | cut -f6 -d:)

echo "Fixing permissions..."
sed -i -e "s/:$ORIG_UID:$ORIG_GID:/:$UID:$GID:/" /etc/passwd
sed -i -e "s/rosbuild:x:$ORIG_GID:/rosbuild:x:$GID:/" /etc/group

chown -R ${UID}:${GID} "${ORIG_HOME}"
echo "done."

echo "Enabling multicast..."
ifconfig eth0 multicast
echo "done."

echo "Initializing Git-LFS..."
if ! sudo -H -u rosbuild -- git lfs install; then
  echo "Git-LFS failed to initialize (this is expected on ARM platforms)."
fi
echo "done."

case "${CI_ARGS}" in
  *--connext*)
    echo "Installing Connext..."
    case "${CI_ARGS}" in
      *--osrf-connext-debs*)
	echo "Installing OSRF-build Connext debs..."
	dpkg -i /tmp/librticonnextdds52_5.2.3-1_amd64.deb
	dpkg -i /tmp/librticonnextdds52-dev_5.2.3-1_amd64.deb
	dpkg -i /tmp/rticonnextdds-tools_5.2.3-1_amd64.deb
	;;
      *)
	echo "Install Connext binaries off RTI website..."
	python3 -u /tmp/rti_web_binaries_install_script.py /tmp/rti-installer.run /home/rosbuild
	mv /tmp/rti_license.dat /home/rosbuild/rti_license.dat
	export RTI_LICENSE_FILE=/home/rosbuild/rti_license.dat
	;;
    esac
    echo "done."
    ;;
  *)
    echo "NOT installing Connext."
    ;;
esac

cd /home/rosbuild/ci_scripts

exec sudo -H -u rosbuild -E -- /bin/sh -c "$*"
