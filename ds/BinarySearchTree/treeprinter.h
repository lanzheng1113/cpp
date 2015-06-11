/*
 * treeprinter.h
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */

#ifndef TREEPRINTER_H_
#define TREEPRINTER_H_
#include <string>
#include <vector>
#include "bst.h"

/**
 * BST边类
 */
struct BSTEdge {
	BSTEdge(const std::string &f,const std::string &t,bool vis=true): from(f), to(t), isVisiable(vis) {
	}
    std::string toString() {
    	if(isVisiable)
    		return from+"->"+to;
    	else
    		return from+"->"+to+"[weight=100 style=invis]";
    }
	std::string from;
	std::string to;
	bool isVisiable;
};
/**
 * 利用绘制二叉树
 * 1)将树形写入.dot文件
 * 2)利用Graphviz程序转换.dot文件为png图片
 *    dot转换为图片阶段 系统必须安装有graphviz并配置有dot命令 否则失效
 *    利用系统命令例如: system ("dot example.dot -Tpng -o 1.png");转换为图片
 *    关于Graphviz更多内容参见:http://www.graphviz.org
 */
class BiTreePrinter {
public:
    static void toPng(const BST *bst,const std::string &desp=std::string(),const BSTNode* pcur=0);
    static  std::string intToString(int i);
    static std::string fontColor,fillColor,currentFillColor,currentFontColor,edgeColor,arrowheadType,width,height,fontsize; // 参数
    static std::string prefix;	// 文件名前缀
    static long fileCounter;	//文件编号
private:
    static void printNull(std::string parentId, std::string virtualId, std::ofstream &stream);
    static void addEdge(std::vector<std::string> &invisNodeVec,std::vector<BSTEdge> &edgeVec,const BSTNode* from);
    static void writePng(std::vector<std::string> &invisNodeVec,std::vector<BSTEdge> &edgeVec,const std::string& desp,const BSTNode* pcur=0);
    static std::string getNextFilename();

};
#endif /* TREEPRINTER_H_ */
