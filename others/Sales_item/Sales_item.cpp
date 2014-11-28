#include "Sales_item.h"

//友元重载>>
std::istream & operator >>(std::istream& in,Sales_item& s)
{
    double price;
	in >> s.isbn >> s.units_sold >>price;
	//检查流的状态
    if(in)
	{
		s.revenue = s.units_sold*price;
	}
	else
	{
		s = Sales_item();
	}
	return in;
}

//友元重载<<
std::ostream& operator <<(std::ostream& out,Sales_item& s)
{
	out << s.isbn << "\t" <<s.units_sold << "\t"
		<< s.revenue << "\t" << s.avg_price();
    return out;
}
Sales_item operator+(const Sales_item& item1,const Sales_item& item2)
{
	Sales_item local(item1);
    local += item2;
	return local;
}
//赋值操作符
Sales_item& Sales_item::operator=(const Sales_item& ref)
{
     isbn = ref.isbn;
	 units_sold = ref.units_sold;
	 revenue = ref.revenue;
	 return *this;
}
//重载+=
Sales_item& Sales_item::operator+=(const Sales_item& ref)
{
   units_sold += ref.units_sold;
   revenue += ref.revenue;
   return *this;
}
double Sales_item::avg_price() const
{
   if(units_sold)
      return revenue/units_sold;
   else
	  return 0;
}
bool Sales_item::same_isbn(const Sales_item& item)  const
{
   return isbn == item.isbn;
}
std::string Sales_item::book() const
{
   return isbn;
}