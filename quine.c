#include <stdio.h>

void main()
{
	const char quin[] = "#include <stdio.h>\n\nvoid main()\n{\t\nconst char quin[] = \"%s\";\t\nprintf(quin, quin);\t\nreturn;\n}\n";
	printf(quin, quin);
	return;
}
