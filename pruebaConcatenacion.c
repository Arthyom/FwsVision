 #include <stdio.h>
 #include <string.h>

	int main (){

		char cadena1 [] = "esta es una cadena muy muy larga";
		char cadena2 [] = "bmp.bmp";

		char * cadenaSuma = (char *) malloc(sizeof(char) * ( strlen(cadena1) + strlen(cadena2) + 4 ) );

		strcpy(cadenaSuma,cadena1);

		strcat(cadenaSuma, cadena2);
		printf("%s\n",cadenaSuma );
		return 0;
	}