/*
 * treeprinter.h
 *
 *  Created on: 2015年5月18日
 *      Author: wangdq
 */

#ifndef TREEPRINTER_H_
#define TREEPRINTER_H_
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "btree.h"

/**
 * B-Tree边类
 */
struct BTreeEdge {
	BTreeEdge(const std::string &f,const std::string &t,int fIndex,int tIndex,bool isWest=true):
		from(f), fromIndex(fIndex),toIndex(tIndex),to(t),west(isWest) {
	}
    std::string toString() const{
    	std::string dir = ":se";
    	std::stringstream ss;
    	ss << fromIndex;
    	std::string fIndex = ss.str();
    	ss << toIndex;
    	std::string tIndex = ss.str();
    	if(west)
    		dir = std::string(":sw");
    	std::stringstream oss;
    		oss << "\"" << from<< "\":f"<< fIndex<< dir<< "->"<< "\""<< to<< "\":f"<< toIndex;
    	return oss.str();
    }
	std::string from;
	int fromIndex,toIndex;
	std::string to;
	bool west;
};
/**
 * 利用Graphviz绘制B-Tree
 * 1)将树形写入.dot文件
 * 2)利用Graphviz程序转换.dot文件为png图片
 *    dot转换为图片阶段 系统必须安装有graphviz并配置有dot命令 否则失效
 *    利用系统命令例如: system ("dot example.dot -Tpng -o 1.png");转换为图片
 *    关于Graphviz更多内容参见:http://www.graphviz.org
 */
class BTreePrinter {
public:
    static std::string fontColor,fillColor,currentFillColor,currentFontColor,edgeColor,arrowheadType,width,height,fontsize; // 参数
    static std::string prefix;	// 文件名前缀
    static long fileCounter;	//文件编号
    static std::string intToString(int i) {
    	std::ostringstream oss;
    	oss << i;
    	return oss.str();
    }
    template<typename T,int M>
    static void toPng(const BTree<T,M>* btree,const std::string &desp=std::string()) {
    	if(btree == 0) {
    				std::cerr << "Printer not bind to any B-Tree"<<std::endl;
    				return;
    			}
    			if(btree->isEmpty())
    				return;
    			std::vector<std::string> visNodeVec;
    			std::vector<BTreeEdge> edgeVec;
    			std::queue<const BTreeNode<T,M>*> nodeQueue;
    			nodeQueue.push(btree->getRoot());
    			while(!nodeQueue.empty()) {		// 广度优先遍历
    				const BTreeNode<T,M>* current = nodeQueue.front();
    			   nodeQueue.pop();
    			   if(!current->isLeaf)
    				   for(int i=0;i <= current->keynum;++i)
    									nodeQueue.push(current->childs[i]);
    			   	addEdge(visNodeVec,edgeVec,current);
    			}
    			writePng(visNodeVec,edgeVec,desp);
    }
private:
    static std::string getNextFilename() {
    	  const std::string ext = ".dot";
		   std::string filename(prefix);
			std::ostringstream oss;
			oss << fileCounter++;
			filename += oss.str();
			filename += ext;
			return filename;
    }
    template<typename T,int M>
    static void addEdge(std::vector<std::string> & visNodeVec,std::vector<BTreeEdge> &edgeVec,
    		const BTreeNode<T,M>* from) {
    	if(from->keynum < 0 ) return;
    		std::string label = from->toString()+"[label=\"";
    		for(int i=0;i < from->keynum;++i) {
    			label += std::string("<f")+intToString(i)+"> "+intToString(from->keys[i]);
    			if(i != from->keynum-1)
    				label += "|";
    		}
    		label+="\"];";
    		visNodeVec.push_back(label);
    		if(from->isLeaf) return;
    		for(int i=0;i < from->keynum;++i)
    			edgeVec.push_back(BTreeEdge(from->toString(),from->childs[i]->toString(),i,from->childs[i]->keynum-1,true));
    		edgeVec.push_back(BTreeEdge(from->toString(),from->childs[from->keynum]->toString(),
    				from->keynum-1,from->childs[from->keynum]->keynum /2,false));
    }
    static void writePng(std::vector<std::string> & visNodeVec,std::vector<BTreeEdge> &edgeVec
    		,const std::string& desp) {
    	long count = fileCounter;
    			std::string filename = getNextFilename();
    			std::ofstream stream(filename.c_str());
    			// print author and contact info
    			stream << "/************************************************" <<std::endl
    						<< "Auto generated by my program which transfer B-Tree to dot file." << std::endl
    						<< "Author: wangdq "  <<std::endl
    						<<  "Time: 2015-06-08" <<std::endl
    						<< "CSDN: http://blog.csdn.net/wangdingqiaoit"<<std::endl
    						<< "************************************************/" <<std::endl<<std::endl;
    			// print description
    			stream << "digraph BTree {" << std::endl;
    			stream << "\tlabel=\"(" << count <<")\t" <<  desp << "\";"<< "labelloc=b;labeljust=center;"<<std::endl;
    			// print settings
    		    stream	<< "\tordering=out" << std::endl
    						<< "\tnode[shape=record,width=" << width << ",height=" <<height << ",fontsize=" << fontsize << ",style=\"filled\", fillcolor=\""
    						<< fillColor << "\",fontcolor=\"" << fontColor << "\"];" << std::endl
    						<< "\tedge[color=\"" << edgeColor << "\", arrowhead=\"" << arrowheadType << "\"];"<< std::endl;
    			//print visible node
    			for(std::vector<std::string>::iterator it = visNodeVec.begin(); it != visNodeVec.end();++it)
    							stream << "\t\t" << *it << std::endl;
    			//print edges
    			stream << "\t/* edges*/" << std::endl;
    			for(std::vector<BTreeEdge>::iterator it = edgeVec.begin(); it != edgeVec.end();++it)
    				   stream <<"\t" << (*it).toString() << std::endl;
    			stream <<  "}"<< std::endl;
    			stream.close();
    			//transfer from dot file to png picture
    			std::string cmd("dot -Tpng");
    			cmd += " "+filename+" -o"+filename+".png";
    			std::system(cmd.c_str());
    			std::cout << "tree saved in file: " << filename<< std::endl;
    }
};
std::string BTreePrinter::fontColor="black",BTreePrinter::fillColor="#FFFFFF",
				BTreePrinter::currentFillColor="red",BTreePrinter::width="0.5",
				BTreePrinter::height="0.5",BTreePrinter::fontsize="16",BTreePrinter::currentFontColor="black",
				BTreePrinter::edgeColor="blue",BTreePrinter::arrowheadType="normal";
long BTreePrinter::fileCounter = 1;
std::string BTreePrinter::prefix="B-Tree";
#endif /* TREEPRINTER_H_ */
