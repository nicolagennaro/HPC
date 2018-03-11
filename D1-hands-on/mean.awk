#!/usr/bin/awk -f

BEGIN{
    sum=0.0;
}
{
    sum+=$1
}

END{
    mean=sum/NR;
    print mean;
}
