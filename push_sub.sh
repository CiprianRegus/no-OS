git checkout -b temp-br
git filter-repo --force --preserve-commit-hashes --path=drivers/platform --refs temp-br --path-rename drivers/platform/:
git pull --rebase origin_subtree_v2 main
git push origin_subtree_v2 temp-br:main
git checkout master
git branch -D temp-br
