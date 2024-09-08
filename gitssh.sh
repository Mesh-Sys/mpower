#!/bin/bash

echo "eval \$(ssh-agent -s)"
echo "ssh-add ~/whiskgit"
echo "ssh-add -l -E sha256"
