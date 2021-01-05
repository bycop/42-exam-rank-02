#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(int n)
{
	long	nb;
	int		i;
	int		save;
	char	c[10];

	nb = n;
	if (nb == 0)
		ft_putchar('0');
	if (nb < 0)
		nb = -nb;
	i = 0;
	while (nb > 0)
	{
		c[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	save = i;
	while (--i >= 0)
		ft_putchar(c[i]);
}

int	digitlen(int nb)
{
	int i;
    int j;

    i = 0;
    j = 10;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
    while (nb >= j && ++i)
        nb /= j;
    return (i + 1);
}

int		ft_printf(const char *str, ...)
{
	int precision;
	int length;
	int i;
	int total;
	va_list va;

	i = 0;
	total = 0;
	length = 0;
	precision = -1;
	va_start(va, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			while ((str[i] >= '0' && str[i] <= '9'))
			{
				length = length * 10 + (str[i] - '0'); 
				i++;
			}
			if (str[i] == '.')
			{
				precision++;
				i++;
				while ((str[i] >= '0' && str[i] <= '9'))
				{
					precision = precision * 10 + (str[i] - '0'); 
					i++;
				}
			}
			if (str[i] == 's')
			{
				char *s = va_arg(va, char *);
				int real = (precision < ft_strlen(s) ? (precision == -1 ? ft_strlen(s) : precision) : ft_strlen(s));
				while (real < length && length != 0)
				{
					total += ft_putchar(' ');
					length--;
				}
				int pre = 0;
				while (pre < real)
				{
					if (s[pre])
						total += ft_putchar(s[pre]);
					pre++;
				}
			}
			if(str[i] == 'd')
			{
				int nb = va_arg(va, int);
				int real = (precision > digitlen(nb) ? precision : digitlen(nb));
				if (nb < 0 && precision < length && precision != -1)
					real ++;
				while (real < length && length != 0)
				{
					total += ft_putchar(' ');
					length--;
				}
				if (nb < 0)
				{
					ft_putchar('-');
					precision++;
				}
				while (precision > digitlen(nb))
				{
					total += ft_putchar('0');
					precision--;
				}
				ft_putnbr(nb);
				total += digitlen(nb);
			}
			if (str[i] == 'x')
			{
				unsigned int nb = va_arg(va, unsigned int);
				char hex[100];	
				unsigned int quotient, remainder;
				int j = 0;

				quotient = nb;
				while (quotient != 0)
				{
					remainder = quotient % 16;
					if (remainder < 10)
						hex[j++] = 48 + remainder;
					else
						hex[j++] = 87 + remainder;
					quotient = quotient / 16;
				}
				int real = (precision > j ? precision : j);
				while (real < length && length != 0)
				{
					total += ft_putchar(' ');
					length--;
				}
				while (precision > j)
				{
					total += ft_putchar('0');
					precision--;
				}
				while (hex[--j])
					total += ft_putchar(hex[j]);
			}
			i++;
		}
		else if (str[i])
			total += ft_putchar(str[i]);
		i++;
	}
	va_end(va);
	return (total + 1);
}

int		main()
{
	printf("\nReal Val: %d\n",printf("\nV: %d\n", 0));
	printf("\nMy Val: %d\n", ft_printf("\nP: %d\n",0));
	ft_printf("Simple test\n");
	ft_printf("");
	ft_printf("--ft_printformat---");
	ft_printf("\n");
	ft_printf("%d", 0);
	ft_printf("%d", 42);
	ft_printf("%d", 1);
	ft_printf("%d", 5454);
	ft_printf("%d", (int)2147483647);
	ft_printf("%d", (int)2147483648);
	ft_printf("%d", (int)-2147483648);
	ft_printf("%d", (int)-2147483649);
	ft_printf("\n");
	ft_printf("%x", 0);
	ft_printf("%x", 42);
	ft_printf("%x", 1);
	ft_printf("%x", 5454);
	ft_printf("%x", (int)2147483647);
	ft_printf("%x", (int)2147483648);
	ft_printf("%x", (int)-2147483648);
	ft_printf("%x", (int)-2147483649);
	ft_printf("%s", "");
	ft_printf("%s", "toto");
	ft_printf("%s", "wiurwuyrhwrywuier");
	ft_printf("%s", NULL);
	ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	ft_printf("\n--Mixed---\n");
	ft_printf("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	ft_printf("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	ft_printf("\n");
	ft_printf("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	ft_printf("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	ft_printf("--1 ft_printflag--\n");
	ft_printf("d0w %0d %0d %0d %0d %0d %0d %0d %0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d4w %4d %4d %4d %4d %4d %4d %4d %4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d10w %10d %10d %10d %10d %10d %10d %10d %10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d4p %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x0w %0x %0x %0x %0x %0x %0x %0x %0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x4w %4x %4x %4x %4x %4x %4x %4x %4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x10w %10x %10x %10x %10x %10x %10x %10x %10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x0p %.0x %.0x %.0x %.0x %.0x %.0x %.0x %.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x4p %.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x10p %.10x %.10x %.10x %.10x %.10x %.10x %.10x %.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s4w ~%4s` ~%4s` ~%4s` ~%4s` ~%4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s10w ~%10s` ~%10s` ~%10s` ~%10s` ~%10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s10p ~%.10s` ~%.10s` ~%.10s` ~%.10s` ~%.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("--2 ft_printflags--\n");
	ft_printf("d0w0p %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d %0.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x0w0p %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x %0.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("--Precision--\n");
	ft_printf("d0w4p %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d %0.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d0w10p %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d %0.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x0w4p %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x %0.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x0w10p %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x %0.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("--Width--\n");
	ft_printf("d4w0p %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d %4.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d10w0p %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d %10.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x4w0p %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x %4.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x10w0p %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x %10.0x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("s4w0p ~%4.s` ~%4.s` ~%4.s` ~%4.s` ~%4.s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s10w0p ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s` ~%10.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("--Width and Precision--\n");
	ft_printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d10w10p %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d %10.10d\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d4w4p %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d %4.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d4w10p %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d %4.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x10w4p %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x %10.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x10w10p %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x %10.10x\n", 0, 1, 42, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x4w4p %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x %4.4x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("x4w10p %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x %4.10x\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s4w4p ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s` ~%4.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	ft_printf("s4w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
}