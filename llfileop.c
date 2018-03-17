/*
 * llfileop.c
 *
 *  Created on: Oct 15, 2009
 *      Author: hankcho
 */

#include "linkedlist.h"
#define MYDBFILE "hw2-data.txt"

int llprint( DA* t )
{

	printf("%s, %s\n",t->lname,t->fname);
	printf("   Mobile: %s\n",t->mobile);
	printf("       SN: %s\n",t->sn);
	printf("  Birthay: %s\n",t->bd);

	return 0;
}

int llgline( FILE* fp, char* str, int size )
{
	char ch;
	int i=0;

	while( !feof(fp) )
	{
		ch = fgetc( fp );

		/* End of line or too many char */
		if( ch == '\n' ||  i == (size-1) )
		{
			str[i]='\0';
			break;
		}
		else
		{
			str[i]= ch;
		}

		i++;
	}
	return i;
}

/* Returns the read records */
int lldbfin( DA* head )
{
	FILE *fp, *fopen();
	int llinsert();
	DA	one;
	int ret=0;

	if( fp = fopen( MYDBFILE, "r") )
	{
		while( !feof(fp) )
		{
			fscanf(fp,"%s",one.lname );
			if(feof(fp)) break;

			fscanf(fp,"%s",one.fname );
			if(feof(fp)) break;

			fscanf(fp,"%s",one.mobile );
			if(feof(fp)) break;

			fscanf(fp,"%s",one.sn ) ;
			if(feof(fp)) break;

			fscanf(fp,"%s",one.bd ) ;
			if(feof(fp)) break;

			llinsert( &one );
			ret++;
		}

		printf("Info> %d records inserted\n",ret );
		fclose(fp);

	}
	else
	{
		printf("Info> File(%s) Not Found\n", MYDBFILE );
	}

	return( ret );
}



/* Returns the number of records recorded */
int lldbfout( DA* head )
{
	FILE *fp, *fopen();
	DA* temp;
	int ret=0;

	if( fp = fopen( MYDBFILE, "w") )
	{
		for(temp=head; temp != 0; temp=temp->next)
		{
			fprintf(fp,"%s\n",temp->lname);
			fprintf(fp,"%s\n",temp->fname );
			fprintf(fp,"%s\n",temp->mobile);
			fprintf(fp,"%s\n",temp->sn);
			fprintf(fp,"%s\n",temp->bd);
			fprintf(fp,"%s\n",temp->extra);

			ret++;
		}

		fprintf(fp,"\n");
		fclose(fp);
		printf("Info> %d records recorded\n", ret );
	}
	else
	{
		printf("Error> File(%s) Writing Error\n", MYDBFILE );
	}
	return( ret );
}
