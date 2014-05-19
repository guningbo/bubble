
#include "tricall.h"

void initIOV(triangulateio &in,BubbleList p,triangulateio &mid,triangulateio &vorout)
{
	in.numberofpoints=p.ListSize();

	in.numberofpointattributes=1;
	in.pointlist=new REAL[2*in.numberofpoints];
	in.pointattributelist=new REAL[in.numberofpoints];
	in.pointmarkerlist=(int *)NULL;
	
	
	BUBBlE *q=NULL;
		q=p.GetHead();
		q=q->next;
	for (int i=0;i<in.numberofpoints;i++)
	{
		in.pointlist[i*2]=q->pointX;
		in.pointlist[i*2+1]=q->pointY;
		in.pointattributelist[i]=q->Attribute;

		q=q->next;
	}
	in.numberofsegments = 0;
	in.numberofholes = 0;
	in.numberofregions = 1;
	in.regionlist=new REAL[4*in.numberofregions];
	in.regionlist[0]=0.0;
	in.regionlist[1]=0.0;
	in.regionlist[2]=1.0;
	in.regionlist[3]=1.0;

	in.trianglelist=(int *)NULL;
	         /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	in.triangleattributelist = (REAL *) NULL;
	in.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	in.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	in.segmentmarkerlist = (int *) NULL;
	in.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	in.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */


	mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
	/* Not needed if -N switch used or number of point attributes is zero: */
	mid.pointattributelist = (REAL *) NULL;
	mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
	mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
	/* Not needed if -E switch used or number of triangle attributes is zero: */
	mid.triangleattributelist = (REAL *) NULL;
	mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	mid.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	mid.segmentmarkerlist = (int *) NULL;
	mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */

	vorout.pointlist = (REAL *) NULL;        /* Needed only if -v switch used. */
	/* Needed only if -v switch used and number of attributes is not zero: */
	vorout.pointattributelist = (REAL *) NULL;
	vorout.edgelist = (int *) NULL;          /* Needed only if -v switch used. */
	vorout.normlist = (REAL *) NULL;         /* Needed only if -v switch used. */
}
/*

REAL GetDistance(REAL ax,REAL ay,REAL ex,REAL ey)
{
	REAL Dist=pow((pow((ax-ex),2.0)+pow((ay-ey),2.0)),1/2.0);
	return Dist;
}

REAL GetSpring(REAL xi,REAL xj,REAL Lij)
{
	REAL temp;
	if(xi>xj)temp=xi-xj-Lij;
	else temp=xi-xj+Lij;
	temp=(-1)*SpringK*temp;
	return temp;
}
REAL GetPlateauEqual(REAL ri,REAL rj)
{
	return ri+rj;
}
//
REAL GetSlope(REAL ax,REAL ay,REAL ex,REAL ey)
{
	return (ax-ex)/(ay-ey);

}


*/