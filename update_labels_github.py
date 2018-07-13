import argparse
import datetime

from github import Github, GithubException, GithubObject


github_api_url = 'https://api.github.com'


# label_dict: name, color
LABEL_DICT = {
    'bug': 'd73a4a',
    # 'hitlist': 'fc6b28',
    'duplicate': 'cccccc',
    'enhancement': 'a2eeef',
    'question': 'd876e3',
    'more-information-needed': '159818',
    'help wanted': '008672',
    # 'claimed': '',
    'wontfix': 'ffffff',
    'ready': '80916d',
    'in progress': 'fad8c7',
    'in review': '388be2',
    'invalid': 'e4e669',
    'good first issue': '7057ff',
    # 'language/cmake': 'fbca04',
    # 'language/c': 'fbca04',
    # 'language/c++': 'fbca04',
    # 'language/python': 'fbca04',
}

REPO_BLACKLIST = [
    'docs.ros2.org',
    'ros2.github.io',
]

MILESTONES_DICT = {
    'untargeted': ['It is unlikely that the maintainers will have time to address these issues. Please provide pull requests if you want these issues to be addressed.', None],
    'bouncy': ['The ROS 2 release "Bouncy Bolson".', datetime.datetime(2018, 6, 22, 7, 0)],
}


def update_labels(commit, repo, label_dict):
    # print('  update label called with repo: %s and labels\n  %s' % (repo.name, label_dict))
    current_labels = [_ for _ in repo.get_labels()]
    current_labels_names = [_.name for _ in current_labels]
    for label, color in label_dict.items():
        # check if label with same name already exists
        if label in current_labels_names:
            idx = current_labels_names.index(label)
            # check if existing label has the right color
            current_label = current_labels[idx]
            if current_label.color == color:
                continue
            print("  -> update color of '{0}' from '{1}' to '{2}'".format(
                    label,
                    current_label.color,
                    color
            ))
            if not commit:
                continue
            try:
                current_label.edit(label, color)
                current_label.update()
            except GithubException as e:
                if e.data['message'] == 'Repository was archived so is read-only.':
                    print('%s has been archived, skipping label update' % repo.name)
                    pass
                else:
                    raise

        else:
            # if label doesn't exist: create it
            print("  -> creating label '%s' with color '%s'" % (label, color))
            if not commit:
                continue
            repo.create_label(label, label_dict[label])


def update_milestones(commit, repo, milestones_dict):
    current_milestones = [milestone for milestone in repo.get_milestones()]
    current_milestones_titles = [milestone.title for milestone in current_milestones]
    current_milestones_due_on = [milestone.due_on for milestone in current_milestones]
    print(current_milestones_due_on)

    for milestone, milestone_infos in milestones_dict.items():
        if milestone in current_milestones_titles:
            idx = current_milestones_titles.index(milestone)
            # check if existing label has the right infos
            current_milestone = current_milestones[idx]
            if current_milestone.description == milestone_infos[0] and current_milestone.due_on == milestone_infos[1]:
                continue
            if current_milestone.description != milestone_infos[0]:
                print("  -> update milestone '{0}' description from '{1}' to '{2}'".format(
                        milestone,
                        current_milestone.description,
                        milestone_infos[0]
                ))
            elif current_milestone.due_on != milestone_infos[1]:
                print("  -> update milestone '{0}' due date from '{1}' to '{2}'".format(
                        milestone,
                        current_milestone.due_on,
                        milestone_infos[1]
                ))
            if not commit:
                continue
            current_milestone.edit(
                milestone, description=milestone_infos[0],
                due_on=milestone_infos[1] if milestone_infos[1] is not None else GithubObject.NotSet)
        else:
            # if milestone doesn't exist: create it
            print("  -> creating milestone '{0}' with description '{1}' and due date '{2}'".format(
                milestone,
                milestone_infos[0],
                milestone_infos[1])
            )
            if not commit:
                continue
            due_on = milestone_infos[1] if milestone_infos[1] is not None else GithubObject.NotSet
            repo.create_milestone(
                milestone, description=milestone_infos[0],
                due_on=due_on)


def main(*, token, commit, orgs, label_dict, milestones_dict):
    gh = Github(token)
    print(orgs)
    for org in orgs:
        print(org)
        organization = gh.get_organization(org)
        org_repos = organization.get_repos()
        for idx, repo in enumerate(org_repos):
            if repo.name in REPO_BLACKLIST:
                continue
            print("processing '%s'" % repo.name)
            update_labels(commit, repo, label_dict)
            print('')
            update_milestones(commit, repo, milestones_dict)
            print('')


if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument(
        '--token',
        required=True,
        help='Github token',)
    argparser.add_argument(
        '--label_dict',
        type=dict,
        default=LABEL_DICT,
        help='dictionary of labels, label_name as key and color as value',)
    argparser.add_argument(
        '--milestones_dict',
        type=dict,
        default=MILESTONES_DICT,
        help='dictionary of milestones, milestone title as key and [description, due_on] as value',)
    argparser.add_argument(
        '--commit',
        action='store_true',
        default=False,
        help='actually modify upstream repo, we encourage to do a dry-run before using this flag',)
    argparser.add_argument(
        '--orgs',
        nargs='+', default=['ament', 'ros2'],
        help='list of organisations to propagate labels to',)
    args = argparser.parse_args()

    main(
        token=args.token,
        commit=args.commit,
        orgs=args.orgs,
        label_dict=args.label_dict,
        milestones_dict=args.milestones_dict
    )
