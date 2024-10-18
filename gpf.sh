#!/bin/bash

# https://stackoverflow.com/questions/1125968/how-do-i-force-git-pull-to-overwrite-local-files
# Ask for y/n input
echo "Do you want to GIT PULL (OVERWRITE)? (y/n): "
read response

# Check if the response is y or n
if [[ $response == "y" ]]; then
  # Run the command
	# Backup your local uncommited changes: 
	##git stash
	# Later, after (git reset), reapply these uncommitted changes: (git stash pop). Which may create merge conflicts.
	# Update all origin/<branch> refs to latest:
	echo "fetching all..."
	git fetch --all
	# Jump to the latest commit on origin/main and checkout those files:
	git reset --hard origin/main
elif [[ $response == "n" ]]; then
  # Do nothing
	echo "Repo still divergent. Please commit your changes or stash them before you merge."
else
  # Invalid input
	echo "Please enter y or n."
fi
