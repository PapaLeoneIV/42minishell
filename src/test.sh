#!/bin/bash

# Start minishell and send input via a here-document
./minishell <<EOF
# Basic commands
echo Hello
ls -l | grep test
cat file.txt > output.txt

# Test handling of pipes and redirections
echo "This is a test" | grep "test"
cat < file.txt > output2.txt
cat file.txt >> append.txt

# Commands with unusual spacing
echo      multiple      spaces
ls -l    |      grep "test"  

# Special characters and quoting
echo "Special characters: * & ^ % # @"
echo "Quoting 'single quotes' inside \"double quotes\""
echo 'Escaping \'single quotes\' inside "single quotes"'
echo \$PATH
echo "Variable expansion \$USER is $USER"

# Command chaining and subshells
mkdir test_dir && cd test_dir && touch newfile && ls
(cd .. && ls -a)

# Nested commands and backticks (old style)
echo "Today's date is \$(date)"
echo "Files: \$(ls | grep file)"

# Complex redirection and pipe combinations
cat < input.txt | grep something | sort | uniq > output.txt

# Escaping characters
echo "Path is \$PATH"
echo "Items in directory are \$(ls)"
echo "Dollar \$sign"

# Misuse of shell syntax (should handle errors or unexpected input gracefully)
cat | | | | echo "This should probably not work"
> > > > outfile.txt
ls -l | | | grep something
echo $(unset PATH) && echo "Path is now empty"

EOF

echo "Script completed. Press Ctrl+D to send EOF and exit minishell."
echo "If the shell is still active, manually check for prompt stability and errors."

# Wait for a period of time or until a keyboard interrupt
# Adjust the time as needed based on how interactive you want to be
sleep 30
