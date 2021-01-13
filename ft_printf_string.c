#include "ft_printf.h"

void	print_char(va_list *ap, t_data_flag *data)
{
	char c;

	c = (char)va_arg(*ap, int);
	data->spec_len = 1;
	if (data->field <= data->spec_len)
		data->field = 0;
	else
		data->field -= data->spec_len;
	if (!data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
	printf_putchar(c, 1);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void	print_string(va_list *ap, t_data_flag *data)
{
	char *s;

//精度を指定してないなら全部表示するので、int_maxにしておけば全部出る
	if (data->precision == -1)
		data->precision = INT_MAX;
//何文字出力するかの計算
	set_print_string(ap, data, &s);

//フィールド幅から空白を表示する数を決める
	if (data->field <= data->spec_len)
		data->field = 0;
	else
		data->field -= data->spec_len;

	if (!data->flag[FLAG_MINUS])
		{
			//フラグ[0]はsだとコンパイルエラー出るけど、0埋めはされてる
			if (data->flag[FLAG_ZERO])
				printf_putchar('0', data->field);
			else
				printf_putchar(' ', data->field);
		}
		//ここがちょっと違う
	write(1, s, data->spec_len);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

//文字数と精度の振り分け。NULLの処理。オリジナル
int	set_print_string(va_list *ap, t_data_flag *data, char **s)
{
	int n;

	if (ap == NULL)
		return (print_null(data, s));
	*s = (char *)va_arg(*ap, char *);
	if (s == NULL)
		return (print_null(data, s));
	n = ft_strlen(*s);
	//指定した精度が文字数より多い⇒すべての文字が表示出来て、0を表示する数は[精度-文字数]
	if (n < data->precision && data->precision != INT_MAX)
	{
		data->spec_len = n;
		data->precision -= n;
	}
	//精度は指定ないのでINT＿MAXが代入されてる。つまり、すべての文字が表示される。0を表示する数は0
	else if (n < data->precision && data->precision == INT_MAX)
	{
		data->spec_len = n;
		data->precision = 0;
	}
	//文字数が精度より大きい⇒表示できるのは精度分。0は表示されない。
	else if (n > data->precision)
	{
		data->spec_len = data->precision;
		data->precision = 0;
	}
	return (n);
}

int	print_null(t_data_flag *data, char **s)
{
	*s = "(null)";
	data->spec_len = 6;
	if (data->spec_len > data->precision)
		data->spec_len = data->precision;
	return (0);
}
