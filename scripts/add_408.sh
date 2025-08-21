#!/usr/bin/env bash
# 记录每日 408 真题练习并自动提交。
# 用法：./scripts/add_408.sh 2010 2012 ...
# 可加可选备注： -m "二叉树+最短路" 或 --note "堆优化 Dijkstra"。
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
README="$REPO_ROOT/README.md"
DATE="$(date +%Y-%m-%d)"
NOTE=""
PROBLEMS=()

while (( "$#" )); do
  case "$1" in
    -m|--note)
      shift; NOTE=${1:-""};;
    -h|--help)
      echo "Usage: $0 [problemIds or filenames] [-m note]"; exit 0;;
    *) PROBLEMS+=("$1");;
  esac
  shift || true
done

if [ ${#PROBLEMS[@]} -eq 0 ]; then
  echo "No problems specified." >&2
  exit 1
fi

PROBLEM_STR=$(IFS=,; echo "${PROBLEMS[*]}")

# 暂存当前修改（不提交）
(cd "$REPO_ROOT" && git add .)

# 生成暂存树的短哈希（不含新 README 行）
HASH=$(cd "$REPO_ROOT" && git write-tree 2>/dev/null || echo "pending")
SHORT=${HASH:0:7}

# 构造新行
NEW_LINE="| $DATE | $PROBLEM_STR | ${NOTE//|/ } | $SHORT |"

# 如果当日已存在则替换
TMP_FILE=$(mktemp)
awk -v date="$DATE" -v newline="$NEW_LINE" 'BEGIN{found=0}
/^<!-- 408_DAILY_START -->/ {print; header=1; next}
/^<!-- 408_DAILY_END -->/ {
  if(!found){print newline}
  print; header=0; next}
header && /^\| [0-9]{4}-[0-9]{2}-[0-9]{2} \|/ {
  split($0,a,"|"); gsub(/^ +| +$/,"",a[2]); if(a[2]==date){print newline; found=1; next}}
{print}' "$README" > "$TMP_FILE"

mv "$TMP_FILE" "$README"

# 添加 README 修改并提交
(cd "$REPO_ROOT" && git add README.md)
MSG="chore(408): $DATE $PROBLEM_STR"
(cd "$REPO_ROOT" && git commit -m "$MSG" >/dev/null && echo "Committed: $MSG" || echo "Nothing to commit (maybe no changes)")

# 推送
(cd "$REPO_ROOT" && git push origin main)

echo "Updated README with: $NEW_LINE"
