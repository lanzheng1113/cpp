// from https://msdn.microsoft.com/en-us/library/6ke686zh.aspx
class Date
{
public:
   Date( int mn, int dy, int yr );
   int getMonth() const;     // 只读成员方法 
   void setMonth( int mn );   // 写入函数,不能为const 
private:
   int month;
};

int Date::getMonth() const
{
   return month;        // 不会修改任何内容
}
void Date::setMonth( int mn )
{
   month = mn;          // 修改成员变量 
}
int main()
{
   Date MyDate( 7, 4, 1998 );
   const Date BirthDate( 1, 18, 1953 );
   MyDate.setMonth( 4 );    // Okay
   BirthDate.getMonth();    // Okay
   BirthDate.setMonth( 4 ); // C2662 Error
}
