#!/bin/bash


cm=$(date)

git add .
git commit -m "$cm"
git branch -M main
git push -u origin main
