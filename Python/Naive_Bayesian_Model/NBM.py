#-*-coding:utf-8 -*-

from nltk.tokenize import WordPunctTokenizer
from nltk.probability import FreqDist

neg_str = ['just plain boring ', 'entirely predictable and lacks energy ', 
			'no surprises and very few laughs']
pos_str = ['very powerful ','the most fun film of the summer']
test_str = 'predictable with no originality'

def count_V(words):
	fdist = FreqDist(words.split())
	tops=fdist.most_common(50)
	return tops

def count_str(words):
	l = words.split()
	return len(l)


if __name__ == '__main__':
	whole_str1 = ''
	whole_str2 = ''
	for words in neg_str:
		whole_str1 += words
	for words in pos_str:
		whole_str2 += words
	V = len(count_V(whole_str1 + ' ' + whole_str2))
	print('V为：%d'%V)
	n_neg = count_str(whole_str1)
	n_pos = count_str(whole_str2)
	print('n- 为：%d'%n_neg)
	print('n+ 为：%d'%n_pos)
	p_neg = float(len(neg_str)) / (len(neg_str)+len(pos_str))
	p_pos = float(len(pos_str)) / (len(neg_str)+len(pos_str))
	print('P(-) 为：%.6f'%p_neg)
	print('P(+) 为：%.6f'%p_pos)

	arr_neg = count_V(whole_str1)
	arr_pos = count_V(whole_str2)
	dic_neg = {}
	dic_pos = {}
	# 统计每个词语的频率
	for words in arr_neg:
		dic_neg[words[0]]= float((words[1]+1)) / (n_neg+V)
		if words[0] not in dic_pos:
			dic_pos[words[0]]= float((0+1)) / (n_pos+V)

	for words in arr_pos:
		dic_pos[words[0]]= float((words[1]+1)) / (n_pos+V)
		if words[0] not in dic_neg:
			dic_neg[words[0]]= float((0+1)) / (n_neg+V)

	print('负面评价每个单词的概率：')
	print(dic_neg)
	print('正面评价每个单词的概率：')
	print(dic_pos)

	# 评价测试
	arr_test = count_V(test_str)
	neg = p_neg
	pos = p_pos
	for words in arr_test:
		if words[0] in dic_neg:
			neg *= dic_neg[words[0]]
		if words[0] in dic_pos:
			pos *= dic_pos[words[0]]

	print('负面评价的概率：%.6f'%neg)
	print('正面评价的概率：%.6f'%pos)

	if neg > pos:
		print('所以这是一条负面评价')
	else:
		print('所以这是一条正面评价')