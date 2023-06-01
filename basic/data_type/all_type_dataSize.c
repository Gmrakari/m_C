#include <stdio.h>
#include <limits.h>
#include <float.h>

/*
** 4字节：int(%d)，unsigned=unsigned int(%u)，long=long int(%ld)，unsigned long(%lu)，float(%f)
** 8字节：double(%lf)，unsigned long long(%llu)，long long=long long int(%lld)
** 12字节：long double(%llf)
**
*/

void funcCharDateSize(void)
{
    int minChar = CHAR_MIN;
    int maxChar = CHAR_MAX;
    int umaxChar = UCHAR_MAX;

    printf("minChar:%d\n", minChar);
    printf("maxChar:%d\n", maxChar);
    printf("umaxChar:%d\n", umaxChar);
    printf("\n");
    return;
}

void funcShortDateSize()
{
    int minShort = SHRT_MIN;
    int maxShort = SHRT_MAX;
    int umaxShort = USHRT_MAX;

    printf("minShort:%hd\n", minShort);
    printf("maxShort:%hd\n", maxShort);
    printf("umaxShort:%hu\n", umaxShort);
    printf("\n");
    return;
}

void funcIntDateSize()
{
    int minInt = INT_MIN;
    int maxInt = INT_MAX;
    long int umaxInt = UINT_MAX;

    printf("minInt:%d\n", minInt);
    printf("maxInt:%d\n", maxInt);
    printf("umaxInt:%ld\n", umaxInt);
    printf("\n");
    return;
}

void funcLongDateSize()
{
    long minLong = LONG_MIN;
    long maxLong = LONG_MAX;
    long unsigned int umaxLong = ULONG_MAX;

    printf("minLong:%ld\n", minLong);
    printf("maxLong:%ld\n", maxLong);
    printf("umaxLong:%lu\n", umaxLong);
    printf("\n");
    return;
}

void funcFloatDateSize()
{
    float minFloat = FLT_MIN;
    float maxFloat = FLT_MAX;

    printf("minFloat:%f\n", minFloat);
    printf("maxFloat:%f\n", maxFloat);
    printf("maxFloat:%g\n", maxFloat);
    printf("\n");
    return;
}

void funcDoubleDateSize()
{
    double minDouble = DBL_MIN;
    double maxDouble = DBL_MAX;

    printf("minDouble:%lf\n", minDouble);
    printf("maxDouble:%lf\n", maxDouble);
    printf("maxDouble:%g\n", maxDouble);
    printf("\n");
}

int main()
{
    funcCharDateSize();
    funcShortDateSize();
    funcIntDateSize();
    funcLongDateSize();
    funcFloatDateSize();
    funcDoubleDateSize();
}
