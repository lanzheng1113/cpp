/*
 * util.h
 *
 *  Created on: 2014年12月24日
 *      Author: wangdq
 */

#ifndef COMMON_H_
#define COMMON_H_
#include <istream>

class Util {
public:
	static bool skipStreamComment(std::istream & stream);
};
class Edge {
public:
	Edge(int s,int d,int val) {
		src = s;
		dest = d;
		edgeVal = val;
	}
	bool operator < (const Edge &edge) {
		  return edgeVal < edge.edgeVal;
	}
public:
	int src,dest;
	int edgeVal;
};
#endif /* COMMON_H_ */
