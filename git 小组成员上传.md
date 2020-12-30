# git 小组成员上传

git remote -v  # 查看仓库情况

origin 是自己仓库的地址

upstream 是fork仓库的地址

## steps：

git pull upstream master    # 同步fork仓库的内容到本地机器

git add .  								# 添加修改的内容

git commit -m "备注的内容 日期之类的"      

git push upstream master  # 修改upstream仓库的内容

git fetch upstream 			  # 获取upstream的内容

git merge upstream/master  

git push 								# 合并到自己的仓库