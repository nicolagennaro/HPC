#!/usr/bin/awk -f

BEGIN{
    sum=0.0;
    square=0.0;
}
{
    sum+=$1
    square+=$1*$1
}

END{
    mean=sum/NR;
    square-=sum*mean;
    square/=(NR-1);
    print mean "\t" sqrt(square);
}
