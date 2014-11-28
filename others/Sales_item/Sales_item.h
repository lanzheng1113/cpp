#ifndef _SALES_ITEM_H_
#define _SALES_ITEM_H_

#include <iostream>
#include <string>

class Sales_item
{
public:
	//构造函数
	Sales_item():units_sold(0),revenue(0.0){}
	Sales_item(std::istream &is) { is >> *this; }

	//析构函数
	~Sales_item(){}
    //复制构造函数
	Sales_item(const Sales_item &orig)
		:isbn(orig.isbn),units_sold(orig.units_sold),
		 revenue(orig.revenue){}

	//常量成员函数
	double avg_price() const;
	bool same_isbn(const Sales_item& item)  const;
	std::string book() const;

	//赋值操作符
	Sales_item& operator=(const Sales_item&);

    //重载+=
	Sales_item& operator+=(const Sales_item&);
	
	//内联友元重载==
	friend bool operator== (const Sales_item& lItem,
		const Sales_item& rItem);

	//内联友元重载!=
	friend bool operator!=(const Sales_item& litem,
		const Sales_item& ritem);

	//友元重载>>
	friend std::istream & operator >>(std::istream&,Sales_item&);
	
    //友元重载<<
	friend std::ostream& operator <<(std::ostream&,Sales_item&);
	
private:
	std::string isbn;
	unsigned units_sold;
	double revenue;
};

//非成员函数，非友元函数
Sales_item operator+(const Sales_item& item1,const Sales_item& item2);


//内联友元函数
inline bool operator== (const Sales_item& lItem,
		const Sales_item& rItem)
	{
		return lItem.units_sold == rItem.units_sold 
			   && lItem.revenue == rItem.revenue
			   && lItem.same_isbn(rItem);
	}

inline bool operator!=(const Sales_item& litem,
	const Sales_item& ritem)
{
	 return !(litem == ritem);
}

#endif