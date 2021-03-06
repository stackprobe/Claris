#include "all.h"

int d2i(double value)
{
	return (int)(value + (value < 0.0 ? -0.5 : 0.5));
}
int s2i(char *line, int minval, int maxval, int defval)
{
	if(m_isEmpty(line) || !strchr("-0123456789", *line))
	{
		return defval;
	}
	int value = atoi(line);
	m_range(value, minval, maxval);
	return value;
}
int s2i_x(char *line, int minval, int maxval, int defval)
{
	int value = s2i(line, minval, maxval, defval);
	memFree(line);
	return value;
}
double toDouble(char *line)
{
	int numer = 0;
	int denom = 0;
	int minus = 0;

	for(char *p = line; *p; p++)
	{
		if('0' <= *p && *p <= '9')
		{
			if(
				IMAX / 10 < numer ||
				IMAX / 10 < denom
				)
				break; // overflow -> 打ち切り

			numer *= 10;
			numer += *p - '0';
			denom *= 10;
		}
		else if(*p == '.')
		{
			denom = 1;
		}
		else if(*p == '-')
		{
			minus = 1;
		}
	}
	if(!denom)
		denom = 1;

	return (double)numer / denom * (minus ? -1 : 1);
}
double toDouble(char *line, double minval, double maxval, double defval)
{
	if(m_isEmpty(line) || !strchr("-.0123456789", *line))
	{
		return defval;
	}
	double value = toDouble(line);
	m_range(value, minval, maxval);
	return value;
}
double toDouble_x(char *line, double minval, double maxval, double defval)
{
	double value = toDouble(line, minval, maxval, defval);
	memFree(line);
	return value;
}
char *xcout(char *format, ...)
{
	char *buffer;
	va_list marker;

	va_start(marker, format);

	for(int size = strlen(format) + 128; ; size *= 2)
	{
		errorCase(IMAX < size);

		buffer = (char *)memAlloc(size + 20);
		int retval = _vsnprintf(buffer, size + 10, format, marker);
		buffer[size + 10] = '\0';

		if(0 <= retval && retval <= size)
			break;

		memFree(buffer);
	}
	va_end(marker);

	return buffer;
}
char *strx(char *line)
{
	return (char *)memClone(line, strlen(line) + 1);
}
void strz(char *&buffer, char *line)
{
	memFree(buffer);
	buffer = strx(line);
}
void strz_x(char *&buffer, char *line)
{
	memFree(buffer);
	buffer = line;
}

#define POUND_FIRST_DELAY 17
#define POUND_DELAY 4

int isPound(int counter)
{
	return (counter) == 1 || POUND_FIRST_DELAY < (counter) && ((counter) - POUND_FIRST_DELAY) % POUND_DELAY == 1;
}
int atoi_x(char *line)
{
	int value = atoi(line);
	memFree(line);
	return value;
}
autoList<char *> *tokenize(char *line, char *delimiters)
{
	autoList<char *> *tokens = new autoList<char *>();
	autoList<char> *token = new autoList<char>();

	for(char *p = line; *p; p++)
	{
		char *d;

		for(d = delimiters; *d; d++)
			if(*d == *p)
				break;

		if(*d)
		{
			token->AddElement('\0');
			tokens->AddElement(token->UnbindBuffer());
		}
		else
			token->AddElement(*p);
	}
	token->AddElement('\0');
	tokens->AddElement(token->UnbindBuffer());

	delete token;
	return tokens;
}
char *untokenize(autoList<char *> *tokens, char *separator)
{
	autoList<char> *buffer = new autoList<char>();

	for(int index = 0; index < tokens->GetCount(); index++)
	{
		if(index)
			buffer->AddElements(separator, strlen(separator));

		char *token = tokens->GetElement(index);
		buffer->AddElements(token, strlen(token));
	}
	buffer->AddElement('\0');
	char *ret = buffer->UnbindBuffer();
	delete buffer;
	return ret;
}

int getZero(void)
{
	return 0;
}
uint getUIZero(void)
{
	return 0;
}
__int64 getI64Zero(void)
{
	return 0;
}
void noop(void)
{
	1; // noop
}
void noop_i(int dummy)
{
	1; // noop
}
void noop_ui(uint dummy)
{
	1; // noop
}
void noop_i64(__int64 dummy)
{
	1; // noop
}

i2D_t makeI2D(int x, int y)
{
	i2D_t pos;

	pos.X = x;
	pos.Y = y;

	return pos;
}
d2D_t makeD2D(double x, double y)
{
	d2D_t pos;

	pos.X = x;
	pos.Y = y;

	return pos;
}

bitList *createBitList(void)
{
	return new bitList();
}
void releaseBitList(bitList *bl)
{
	delete bl;
}

void my_memset(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
	{
		((uchar *)block)[index] = fillValue;
	}
}
int isfilled(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
		if(((uchar *)block)[index] != fillValue)
			return 0;

	return 1;
}
int isSame(autoList<uchar> *binData1, autoList<uchar> *binData2)
{
	if(binData1->GetCount() != binData2->GetCount())
		return 0;

	for(int index = 0; index < binData1->GetCount(); index++)
		if(binData1->GetElement(index) != binData2->GetElement(index))
			return 0;

	return 1;
}

double getAngle(double x, double y)
{
	if(y < 0.0) return PI * 2.0 - getAngle( x, -y);
	if(x < 0.0) return PI * 1.0 - getAngle(-x,  y);

	if(x == 0.0) return PI / 2.0;
	if(y == 0.0) return 0.0;

	double r1 = 0.0;
	double r2 = 0.5 * PI;
	double rm;
	double t = y / x;

	for(int count = 10; ; count--) // 10回で、およそ 0.000767 以下の誤差になる。
	{
		rm = (r1 + r2) / 2.0;

		if(!count)
			break;

		if(t < tan(rm))
			r2 = rm;
		else
			r1 = rm;
	}
	return rm;
}
double getAngle(double x, double y, double originX, double originY)
{
	return getAngle(x - originX, y - originY);
}
void rotatePos(double rot, double &x, double &y)
{
	double w;

	w = x * cos(rot) - y * sin(rot);
	y = x * sin(rot) + y * cos(rot);
	x = w;
}
void rotatePos(double rot, double &x, double &y, double originX, double originY)
{
	x -= originX;
	y -= originY;

	rotatePos(rot, x, y);

	x += originX;
	y += originY;
}
