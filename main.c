#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include<string.h>

void convertToBinary1(uint16_t uDec)
{
    if (uDec > 1)
    {
        convertToBinary(uDec / 2);
    }
        printf("%d", uDec%2);

}

uint8_t BinaryToBCD0(uint32_t* pulResult, uint16_t uBinary)
{
    int8_t BitCount;
    uint16_t uBit;
    uint8_t resultMax;
    BitCount=0;
    uBit=0;
    resultMax=0;
    for(BitCount;BitCount>0;BitCount--)
    {
        for(int i=0;i<=resultMax;i++)
        {
            if(((*pulResult>>(4*i)) & ((1<<4)-1))>=5)
            {
                *pulResult+=((1<<2)-1)<<(4*i);
            }
        }
        if((*pulResult & (1<<(3+(4*resultMax))))!=0)
        {
            resultMax++;
        }
        uBit=uBinary & (1<<(BitCount-1));
        if(uBit==0)
        {
            *pulResult=(*pulResult<<1) & (~(1));
        }
        else
        {
            *pulResult=(*pulResult<<1) | (1);
        }
    }
    return resultMax;
}


uint8_t BinaryToBCD(uint32_t* pulResult, uint16_t uBinary)
{
    int8_t BitCount;
    uint8_t resultMax;  // bLenght
    resultMax=1;
    for(BitCount=15; BitCount>=0; BitCount--)
    {
//		---------------------------------------------------1
//         uint32_t uCheckValue;
//         uint32_t uAddValue;
//         uint32_t uMask;
//         uMask=0x0F;
//         uAddValue=3;
//         uCheckValue=5;
//         while((*pulResult)>(uMask>>4))
//         {
//             if(uCheckValue<=((*pulResult) & uMask))
//             {
//                 (*pulResult)+=uAddValue;
//             }
//             uMask<<=4;
//             uAddValue<<=4;
//             uCheckValue<<=4;
//             printf("%lu\n", *pulResult);
//         }
//
//		-----------------------------------------------------2
        for(int i=0;i<resultMax; i++)
        {
            uint16_t uShiftBitCount;
            uint8_t bResultValue;
            uShiftBitCount=(i<<2);
            bResultValue=(((*pulResult)>>uShiftBitCount) & 0x0F);
            if(5<=bResultValue)
            {
                (*pulResult)+=((((uint32_t)3)<<uShiftBitCount));
            }


        }
        (*pulResult)<<=1;
        if(uBinary & (1<<BitCount))
        {
            (*pulResult)|=1;
        }
        if((*pulResult)>>(4*resultMax))
        {
            resultMax++;
        }
//        -----------------------------------------------------3
//         uint8_t bValue;
//         bValue=0;
//         if(uBinary & (1<<BitCount))
//         {
//             bValue=1;
//         }
//         bValue=((uBinary>>BitCount) & 1);
//         for(int i=0;i<=resultMax; i++)
//         {
//             uint16_t uShiftBitCount;
//             //uShiftBitCount=(4*i);
//             uShiftBitCount=(i<<2);
//             bValue|=(((*pulResult)>>uShiftBitCount)<<1);
//             if(10<=bValue)
//             {
//                 bValue+=6;
//             }
//             (*pulResult)&=(~(0x0F<<uShiftBitCount);
//             (*pulResult)|=(((bValue & 0x0F)<<uShiftBitCount));
//             bValue>>=4;
//         }
//        if(0<bValue)
//        {
//            resultMax++;
//        }
//		-----------------------------------------------------4
    }
    return resultMax;
}

int main()
{
    uint32_t ulResultVal;
    uint32_t* pulResultVal=&ulResultVal;
    uint16_t uBinaryNum;
    scanf("%d", &uBinaryNum);
    convertToBinary(uBinaryNum);
    printf("\n");
    for(int i=BinaryToBCD(pulResultVal,uBinaryNum);i>=0;i--)
    {
        printf("%d ", (ulResultVal>>(4*i)) & (0x0F));
    }
}
