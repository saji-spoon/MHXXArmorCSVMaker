MHXXシミュ用CSV生成
==== 

防具情報を入力するとシミュ用CSVとして吐き出します。  
（すでにCSVが存在する場合は末尾に付加）  
MHXのシミュでMHXX用の防具をシミュしたいけど防具情報がない！という場合の手動入力用。  
  
メリット： 
* 防具名-スキル名-スキルポイントのテーブル形式なので装備一式を一括で入力すればスキル名入力の手間が省ける
* 部位ごとに分かれているCSVをそれぞれ編集する手間が省ける

## 使い方
* workディレクトリ以下にシミュ用CSV（防具情報）を入れる
  * MHX_EQUIP_HEAD.csv
  * MHX_EQUIP_BODY.csv
  * MHX_EQUIP_ARM.csv
  * MHX_EQUIP_WST.csv
  * MHX_EQUIP_LEG.csv
* ツールを起動
* 入力
![input](https://github.com/saji-spoon/MHXXArmorCSVMaker/blob/media/pic_028.png)
* [OK]
* 出力内容を確認して[Yes]

## 仕様
* あくまでMHX用のシミュで無理やりMHXXの防具をシミュしたい用のものなので以下の要素は無視されます。ゲーム内で未出の防具を入力するのは非推奨
  * 出現時期
  * 男女別防具
  * 素材
  * レア度
  * 耐性
* 剣士・ガンナーを選択しても頭装備だけは両対応で出力されます
