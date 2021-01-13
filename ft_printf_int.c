#include "ft_printf.h"


void print_int(va_list *ap, t_data_flag *data)
{
	long long num;

	num = va_arg(*ap, int);
	//フィールド、精度の数を数える関数
	get_putlen_di(data, num);
//フラグに[-][0]どちらもない場合は空白を表示
	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);
//負の値ならマイナスを表示
	put_minus(num);
//フラグ[0]だけなら0をフィールド＋精度ぶん表示、そうじゃないなら精度分だけ表示
	if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);
//負の数だったら正の数にする
	if (num < 0)
		num *= -1;
//数値が0じゃないなら表示する
//数値が0で精度が0じゃない場合の0の表示はココじゃなくて、上の精度の部分でやってる
	if (num)
		putnbr_diux(num, *data);
//フラグ[-]があるなら左詰めなので、空白を表示する
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void	get_putlen_di(t_data_flag *data, long long num)
{
//精度が指定されたら[0]フラグは無視される
	if (data->flag[FLAG_ZERO] && (data->precision == -1))
		data->flag[FLAG_ZERO] = 1;
	else
		data->flag[FLAG_ZERO] = 0;

//数値の桁数を求める。この関数だと数値が0だと桁も0になるので注意
	data->spec_len = get_digit_di(num);

//ここでいう「精度」は０を表示する数。実際の定義とは違うし、混同してるので注意。
//桁数が精度よりも大きくて、数値が0かつ精度が0なら表示しない。数値が0で精度が0じゃないなら1
//桁数が精度よりも小さいなら「精度」は「精度-桁数」
	if (data->precision <= data->spec_len)
		data->precision = (num == 0 && data->precision);
	else
		data->precision -= data->spec_len;

//負の値だと、桁数にマイナス記号分を足す
	if (num < 0)
		data->spec_len += data->precision + 1;
	else
		data->spec_len += data->precision;

//ここでいう「フィールド幅」は空白の数。実際の定義とは違うので注意
//桁数がフィールド幅より大きければ、空白は表示されない
//桁数がフィールド幅より小さければ、空白は「フィールド幅-桁数」分表示される
	if (data->field <= data->spec_len)
		data->field = 0;
	else
		data->field -= data->spec_len;
}


void print_unsigned(va_list *ap, t_data_flag *data)
{
	unsigned long long num;

	num = va_arg(*ap, unsigned int);

	get_putlen_ux(data, num);

	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);

	if (data->flag[FLAG_SHARP] && num != 0 && data->specifier != 2)
		{
		if (data->specifier == 3)
			write(1, "0x", 2);
		else
			write(1, "0X", 2);
		}

	if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);

	if (num)
		putnbr_diux(num, *data);

	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}

void	get_putlen_ux(t_data_flag *data, unsigned long long num)
{

	if (data->flag[FLAG_ZERO] && (data->precision == -1))
		data->flag[FLAG_ZERO] = 1;
	else
		data->flag[FLAG_ZERO] = 0;

	data->spec_len = get_digit_ux(num, *data);

	if (data->precision <= data->spec_len)
		data->precision = (num == 0 && data->precision);
	else
		data->precision -= data->spec_len;

//フラグ[#]がある場合「0x」を表示するので桁数には2を足す
	if (data->flag[FLAG_SHARP] && num != 0 && data->specifier != SPEC_U)
		data->spec_len += data->precision + 2;
	else
		data->spec_len += data->precision;

	if (data->field <= data->spec_len)
		data->field = 0;
	else
		data->field -= data->spec_len;
}

void	print_pointer(va_list *ap, t_data_flag *data)
{
	unsigned long num;
//ポインタは16進数
	data->specifier = SPEC_SX;
//0xを表示させるために「＃」フラグがある事にする。get_putlen_uxで使う
	data->flag[FLAG_SHARP] = 1;
//値が0（NULL）の時は他のと処理が違う。
	if ((num = (unsigned long)va_arg(*ap, void *)) == 0)
	{
//精度が指定されてなければデフォルトの１にする。そうじゃなければそのままの値。精度が0でも0にしておく。
		if (data->precision == -1)
			data->precision = 1;
//表示桁数は精度に「0x」分の2を足す。NULLでも[0x0]と表示されるので桁数は３になる
		data->spec_len = 2 + data->precision;

		if (data->field <= data->precision)
			data->field = 0;
		else
			data->field -= data->precision;
	}
//値が0じゃなければunsignedの時と同じ。値0、精度0の時はprecisionが0になるので「0x」だけ表示される。
//「＃」がある事になってるので、precision(=0)に2を足してる。
	else
		get_putlen_ux(data, num);

	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);

//フィールド幅の空白の後に「0x」
	write(1, "0x", 2);

		if (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO])
		printf_putchar('0', data->precision + data->field);
	else
		printf_putchar('0', data->precision);

	if (num)
		putnbr_diux(num, *data);

	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}
