
#include "tricall.h"

void initIn(triangulateio &in,BubbleList p)
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
	in.numberofregions = 0;

	in.trianglelist=(int *)NULL;
	in.triangleattributelist = (REAL *) NULL;
	in.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
	/* Needed only if segments are output (-p or -c) and -P not used: */
	in.segmentlist = (int *) NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	in.segmentmarkerlist = (int *) NULL;
	in.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
	in.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */
	
}
void initOV(triangulateio &mid,triangulateio &vorout)
{
mid.pointlist = (REAL *) NULL;            /* Not needed if -N switch used. */
/* Not needed if -N switch used or number of point attributes is zero: */
mid.pointattributelist = (REAL *) NULL;
mid.pointmarkerlist = (int *) NULL; /* Not needed if -N or -B switch used. */
mid.numberofpoints=0;
mid.numberofpointattributes=0;
mid.trianglelist = (int *) NULL;          /* Not needed if -E switch used. */
/* Not needed if -E switch used or number of triangle attributes is zero: */
mid.triangleattributelist = (REAL *) NULL;
mid.numberoftriangles=0;
mid.numberofcorners=0;
mid.neighborlist = (int *) NULL;         /* Needed only if -n switch used. */
/* Needed only if segments are output (-p or -c) and -P not used: */
mid.segmentlist = (int *) NULL;
/* Needed only if segments are output (-p or -c) and -P and -B not used: */
mid.segmentmarkerlist = (int *) NULL;
mid.numberofsegments=0;
mid.edgelist = (int *) NULL;             /* Needed only if -e switch used. */
mid.edgemarkerlist = (int *) NULL;   /* Needed if -e used and -B not used. */
mid.numberofedges=0;
vorout.pointlist = (REAL *) NULL;        /* Needed only if -v switch used. */
/* Needed only if -v switch used and number of attributes is not zero: */
vorout.pointattributelist = (REAL *) NULL;
vorout.numberofpoints=0;
vorout.edgelist = (int *) NULL;    /* Needed only if -v switch used. */
vorout.numberofedges=0;
vorout.normlist = (REAL *) NULL;   /* Needed only if -v switch used. */
vorout.numberofpointattributes=0;
}

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
REAL GetPlateauEqual(REAL ri,REAL rj)// 等式
{
	return ri+rj;
}

REAL GetSlope(REAL ax,REAL ay,REAL ex,REAL ey)//获取斜角度
{
	 return (ax-ex)/(ay-ey);

}

int IsStable(REAL ax,REAL ay,REAL ra,REAL ex,REAL ey,REAL re)
{
	if(GetPlateauEqual(ra,re)==GetDistance(ax,ay,ex,ey))return 1;
	else return 0;
}

void AddPoint(int *b,int point)
{	int flag=0;
	for(int i=1;i<=b[0];i++)
	{
		if(b[i]==point)
			{
				flag=1;
				break;
			}
	}
	if( flag==0)
	{
		b[b[0]+1]=point;
		b[0]=b[0]+1;
	}
}
void DynamicBubble(triangulateio &in,triangulateio &mid,REAL *Velocity)
{
	int a[100][50]={{0}};
	for(int i=0;i<mid.numberoftriangles;i++)
	{
		AddPoint(a[mid.trianglelist[3*i]],mid.trianglelist[3*i+1]);
		AddPoint(a[mid.trianglelist[3*i]],mid.trianglelist[3*i+2]);
		AddPoint(a[mid.trianglelist[3*i+1]],mid.trianglelist[3*i]);
		AddPoint(a[mid.trianglelist[3*i+1]],mid.trianglelist[3*i+2]);
		AddPoint(a[mid.trianglelist[3*i+2]],mid.trianglelist[3*i]);
		AddPoint(a[mid.trianglelist[3*i+2]],mid.trianglelist[3*i+1]);
	}

	for(int i=0;i<mid.numberofpoints;i++)
	{	
		REAL fx=0,fy=0;
		REAL xi,yi,ri;
		xi=mid.pointlist[2*i];
		yi=mid.pointlist[2*i+1];
		ri=mid.pointattributelist[i];
		for(int j=1;j<=a[i][0];j++)
		{
		 REAL xj,yj,rj;
		 xj=mid.pointlist[2*j];
		 yj=mid.pointlist[2*j+1];
		 rj=mid.pointattributelist[j];
		 REAL Lij=GetPlateauEqual(ri,rj);
		 fx=fx+GetSpring(xi,xj,Lij);
		 fy=fy+GetSpring(yi,yj,Lij);
		}
		REAL accX=fx/0.1;
		REAL accY=fx/0.1;
		REAL sx=Velocity[2*i]*Pertime+(1/2.0)*accX*pow(Pertime,2.0);
		REAL sy=Velocity[2*i+1]*Pertime+(1/2.0)*accY*pow(Pertime,2.0);
		in.pointlist[2*i]=in.pointlist[2*i]+sx;
		in.pointlist[2*i+1]=in.pointlist[2*i+1]+sy;
		Velocity[2*i]=Velocity[2*i]+accX*Pertime;
		Velocity[2*i+1]=Velocity[2*i+1]+accY*Pertime;
	}
}



