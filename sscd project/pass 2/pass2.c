#include<stdio.h>
//#include<conio.h>
#include<string.h>
main ()
{
  FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8;
  char rec[20], name[20], len[20], t[20], string[1000], mod[40][40], est1[20],
    est2[20], est4[20], sign[40][1], temp;
  int ptn1[20][20], ptn2[20][20];
  int l, h = 0, lent[20], i, st, m1, m2, start[20], add[20], k = 0, est3, z1 =
    0, val[40], ptn[40], offset[40], j, num, progstart, count = 0;
  fp1 = fopen ("dllin.txt", "r");
  fp2 = fopen ("estab.txt", "r");
  fp3 = fopen ("ntemp.txt", "w");
  fp4 = fopen ("memory.txt", "w");
  fp6 = fopen ("six.txt", "w");
  fscanf (fp1, "%s%s%x%s", rec, name, &st, len);

  for (l = 0; l < 3; l++)
    {
      if (l == 1)
			fp3 = fopen ("ntempb.txt", "w");
      if (l == 2)
		fp3 = fopen ("ntempc.txt", "w");
     fscanf (fp1, "%s", t);

      do
	{
	  if (strcmp (t, "T") == 0)
	    {
	      fscanf (fp1, "%x%x", &start[h], &lent[h]);
	      if (h != 0)
			{
		  		for (i = 0;i < (start[h] - (start[h - 1] + lent[h - 1])); i++)
		    		fprintf (fp3, "x");
		    	
			}	
	      	h++;
	       fscanf (fp1, "%s", t);
	       do
			{
		  		fprintf (fp3, "%s", t);
		  		fscanf (fp1, "%s", t);
			}while ((strcmp (t, "T") != 0) && (strcmp (t, "M") != 0));
	    }
	  else if (strcmp (t, "M") == 0)
	    {
	      fscanf (fp1, "%x%x%s%s", &ptn[k], &offset[k], sign[k], mod[k]);
	      fscanf (fp2, "%s%s%x%s", est1, est2, &est3, est4);
	      progstart = est3;
	      do
		{
		  if (strcmp (mod[k], est2) == 0)
		    {
		      val[z1] = est3;
		      z1++;
		      break;
		    }
		  else if (strcmp (mod[k], est1) == 0)
		    {
		      val[z1] = est3;
		      z1++;
		      break;
		    }
		  fscanf (fp2, "%s%s%x%s", est1, est2, &est3, est4);
		}while (!feof (fp2));
	      rewind (fp2);
	      fscanf (fp1, "%s", t);
	      k++;
	    }
	  else if (strcmp (t, "E") == 0)
	    {
	      fscanf (fp1, "%s", t);
	      if (l != 2)
			fscanf (fp1, "%s%s%x%s", rec, name, &st, len);
	      break;
	    }
	  else if (strcmp (t, "R") == 0)
	    {
	      while (strcmp (t, "T") != 0)
				fscanf (fp1, "%s", t);
	    }
	  else if (strcmp (t, "D") == 0)
	    {
	      while (strcmp (t, "R") != 0)
				fscanf (fp1, "%s", t);
	    }
	} while (1);
      fclose (fp3);
      for (i = 0; i < k; i++)
	{
	  if (l == 0)
	    fp3 = fopen ("ntemp.txt", "r+");
	  if (l == 1)
	    fp3 = fopen ("ntempb.txt", "r+");
	  if (l == 2)
	    fp3 = fopen ("ntempc.txt", "r+");
	  fp5 = fopen ("temp1.txt", "w");
	  fseek (fp3, (ptn[i] * 2) + 1, 0);
	  for (j = 0; j < offset[i]; j++)
	    {
	      fscanf (fp3, "%c", &temp);
	      fprintf (fp5, "%c", temp);
	    }
	  fprintf (fp5, "\n");
	  fclose (fp5);
	  fp5 = fopen ("temp1.txt", "r");
	  fscanf (fp5, "%x", &num);
	  if (sign[i][0] == '+')
	    {
	      num = num + val[i];
	      fseek (fp3, (ptn[i] * 2) + 1, 0);
	      if (offset[i] == 5)
		fprintf (fp3, "0%x", num);
	      else
	      	fprintf (fp3, "00%x", num);
	    }
	  else
	    {
	      num = num - val[i];
	      fseek (fp3, (ptn[i] * 2) + 1, 0);
	      fprintf (fp3, "00%x", num);
	    }
	  fclose (fp3);
	  fclose (fp5);
	}
      k = 0;
      h = 0;
      z1 = 0;
    }
  fp3 = fopen ("ntemp.txt", "r");
  fscanf (fp3, "%s", string);
  fclose (fp3);
  fprintf (fp6, "%s", string);
  fp3 = fopen ("ntempb.txt", "r");
  fscanf (fp3, "%s", string);
  fclose (fp3);

  fprintf (fp6, "%s", string);
  fp3 = fopen ("ntempc.txt", "r");
  fscanf (fp3, "%s", string);
  fclose (fp3);
  fprintf (fp6, "%s", string);
  fclose (fp6);
  fp6 = fopen ("six.txt", "r");
  fscanf (fp6, "%s", string);
  for (i = 0; i < strlen (string); i++)
    {
      if (i == 0)
	{
	  fprintf (fp4, "%x\t", progstart);
	  progstart += 16;
	}
      if ((i % 8 == 0) && (i != 0))
	fprintf (fp4, "\t");
      if ((i % 32 == 0) && (i != 0))
	{
	  fprintf (fp4, "\n");
	  fprintf (fp4, "%x\t", progstart);
	  progstart += 16;
	}
      fprintf (fp4, "%c", string[i]);
    }
  return 0;
}
