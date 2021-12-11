#pragma once

#ifndef _RTDB_DEFINE_H__
#define _RTDB_DEFINE_H__


#define RTDB_TAGNAME_LENGTH 48		//��������󳤶�
#define RTDB_TAGDESC_LENGTH 32		//���������󳤶�
#define RTDB_TAGUNIT_LENGTH 16		//��㵥λ��󳤶�

#define RTDB_MAX_DATACOUNT  1024	//������ݸ���

#define RTDB_DATATYPE_RAW 0			//����������ͣ�ԭʼֵ
#define RTDB_DATATYPE_MAX 1			//����������ͣ����ֵ
#define RTDB_DATATYPE_MIN 2			//����������ͣ���Сֵ
#define RTDB_DATATYPE_AVG 3			//����������ͣ�ƽ��ֵ
#define RTDB_DATATYPE_SNP 4			//����������ͣ�����ֵ

#define RTDB_DATASTATUS_GOOD 0			//�������״̬��������
#define RTDB_DATASTATUS_BAD 1			//�������״̬��������
#define RTDB_DATASTATUS_MANUAL 2		//�������״̬���˹�����
#define RTDB_DATASTATUS_TAGNOTEXIST 3	//�������״̬������������
#define RTDB_DATASTATUS_WRITESUCCESS 4	//�������״̬��д��ɹ�
#define RTDB_DATASTATUS_DATANOTEXIST 5	//�������״̬�����ݲ�����
#define RTDB_DATASTATUS_WRITEFAILED  6  //�������״̬������д��ʧ��

#define RTDB_RETURNSTATUS_SUCCESS   0        //��ѯ�ɹ�
#define RTDB_RETURNSTATUS_NETECP    -1       //�����쳣
#define RTDB_RETURNSTATUS_DATABASEECP -2     //���ݿ��쳣
#define RTDB_RETURNSTATUS_SYSECP    -3       //ϵͳ�쳣
#define RTDB_RETURNSTATUS_OTHERECP   -4		 //�����쳣
#define RTDB_RETURNSTATUS_POINTNOEXIST   -5  //��㲻����
#define RTDB_RETURNSTATUS_DATANOEXIST    -6  //���ݲ�����
#define RTDB_RETURNSTATUS_DBFUNCECP     -7   //���ݿ⺯��ִ��ʧ��
#define RTDB_RETURNSTATUS_DBFUNCTO      -8   //���ݿ⺯��ִ�г�ʱ

#define RTDB_TAGTYPE_A 1		//������ͣ�ģ����
#define RTDB_TAGTYPE_D 0		//������ͣ�������


//***************************************
//������ݽṹ��
//***************************************
typedef struct TagData_struct{
	double			value;		//���ص����ֵ
	long    		time;		//���ص��ʱ�䣬��
	int 			status;		//���ص��״̬
}TagData;


//**************************************
//��ѯ��ʷ��¼������Ľṹ
//**************************************
typedef struct ReadHiDataRequest_struct{
	long stTime;				//��ѯ���¼�Ŀ�ʼʱ�䣬��
	long enTime;				//��ѯ���¼�Ľ���ʱ�䣬��
	long tPeriod;			    //��ѯ��ֵ��ʱ��������
	int	 reqType;				//��ѯ���������ͣ�ԭʼ=0�����=1����С=2��ƽ��=3,����=4��
	char pointName[RTDB_TAGNAME_LENGTH];	    //�������������
}ReadHiDataRequest;



//************************************
//�����Ϣ�ṹ��
//************************************
typedef struct TagInfo_struct{
	double max;
	double min;
	char   unit[RTDB_TAGUNIT_LENGTH];
	char   desc[RTDB_TAGDESC_LENGTH];
	char   name[RTDB_TAGNAME_LENGTH];
}TagInfo;

//************************************
//�����м�¼��������ݽṹ��
//************************************
typedef struct InsertData_struct{
	int		  type;			//Ϊ0��Ϊ��������Ϊ1��Ϊ������
	int		  status;		//д����¼��״̬
	double    value;		//д����¼��ֵ
	long 	  time;			//д����¼��ʱ�䣬��
	char      pointName[RTDB_TAGNAME_LENGTH];	//д������������
}InsertData;


#endif