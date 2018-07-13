#!/usr/bin/env python3
import sys

from argparse import ArgumentParser
from github import Github

# 20e2e9cd589f0550c74ac96e5d5047ade48ff982
DEFAULT_ORG_NAMES = ['ament', 'ros2']
DEFAULT_BOT_TEAM_NAME = 'bots'
DEFAULT_BOT_USER_NAMES = ['ros-pull-request-builder']

def main(argv=sys.argv[1:]):
    argparser = ArgumentParser()
    argparser.add_argument(
        '--token',
        required=True,
        help='GitHub access token. Needs at least org:admin permissions.')
    argparser.add_argument(
        '--orgs',
        nargs='+', default=DEFAULT_ORG_NAMES,
        help='List of organizations to receive updates')
    argparser.add_argument(
        '--bots-team',
        default=DEFAULT_BOT_TEAM_NAME,
        help='Name to use for the bots team.')
    argparser.add_argument(
        '--bot-users',
        nargs='+',
        default=DEFAULT_BOT_USER_NAMES,
        help='List of GitHub usernames to be added to the bots team.')
    argparser.add_argument(
        '--commit',
        action='store_true',
        default=False,
        help='Actually make changes to organizations. Doing a dry-run first is recommended.')
    argparser.add_argument(
        '--quiet',
        action='store_true',
        default=False,
        help='Supress informational messages. Errors will still be displayed.')
    args = argparser.parse_args(argv)

    github_api = Github(args.token)
    for org_name in args.orgs:
        update_org_bots_team(github_api,
            org_name,
            args.bots_team,
            args.bot_users,
            commit=args.commit,
            verbose=not(args.quiet))


def update_org_bots_team(github_api,
    org_name,
    bots_team_name=DEFAULT_BOT_TEAM_NAME,
    bot_user_names=DEFAULT_BOT_USER_NAMES,
    commit=False,
    verbose=True):

    org = github_api.get_organization(org_name)
    bot_users = [github_api.get_user(login) for login in bot_user_names]
    bots_team = find_or_create_bots_team(org, bots_team_name, commit=commit, verbose=verbose)
    if bots_team is None and not commit:
        # Dry run of later functions cannot complete without a bots_team.
        print("Would add members: {} to '{}' team".format(
            ', '.join([bot.login for bot in bot_users]),
            bots_team_name))
        print("Would add admin permissions to the following repos for '{}' team".format(bots_team_name))
        print('\n'.join([repo.full_name for repo in org.get_repos('all')]))
        sys.exit(0)
    update_bots_team_members(bots_team, bot_users, org, commit=commit, verbose=verbose)
    update_bots_team_repos(bots_team, org.get_repos('all'), commit=commit, verbose=verbose)


def find_or_create_bots_team(organization, team_name, repos=[], commit=False, verbose=True):
    bots_team = [team for team in organization.get_teams() if team.name == team_name]
    if bots_team:
        return bots_team[0]
    elif commit:
        if verbose:
            print("Creating team '{}' in organization '{}'".format(team_name, organization.login))
        return organization.create_team(team_name, repos, 'admin', 'closed')
    else:
        print("Would create team '{}' in organization '{}'.format(team_name, organization.login)")


def update_bots_team_repos(bots_team, repos, commit=False, verbose=True):
    for repo in repos:
        if commit:
            if verbose:
                print("Granting '{}' team admin permission on '{}'".format(
                    bots_team.name, repo.full_name))
            bots_team.set_repo_permission(repo, 'admin')
        else:
            print("Would grant '{}' team admin permission on '{}'".format(
                bots_team.name, repo.full_name))


def update_bots_team_members(bots_team, bot_users, organization, commit=False, verbose=True):
    for bot in bot_users:
        if not organization.has_in_members(bot):
            if commit:
                print("WARNING: {} was not a member of the {} organization and must accept the invitation to join".format(
                    bot.login, organization.login))
                organization.add_to_members(bot, 'member')
        if not bots_team.has_in_members(bot):
            if commit:
                if verbose:
                    print("Adding user '{}' to '{}' team".format(bot.login, bots_team.name))
                bots_team.add_membership(bot, 'member')
            else:
                print("Would add user '{}' to '{}' team of '{}' organization".format(
                    bot.login, bots_team.name, organization.login))

if __name__ == '__main__':
    main(sys.argv[1:])
