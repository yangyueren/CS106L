//
// Created by yryang on 2020/2/21.
//

#ifndef CPPTEST_CONSTEXPRESSION_HPP
#define CPPTEST_CONSTEXPRESSION_HPP



//constexpr int getConst(){
//    const int a = 4;
//    static_assert(a > 3, "assert fail");
//    return a;
//}

struct Date{
public:
    constexpr Date(int y, int m, int d):year(y), month(m), day(d){}
    constexpr const int getYear() const{return year;}
    constexpr const int getMonth() const{return month;}
    constexpr const int getDay() const {return day;}

private:
    int year;
    int month;
    int day;

};

//constexpr Date P{1949,12,2};
//constexpr int mon = P.getMonth();


#endif //CPPTEST_CONSTEXPRESSION_HPP
