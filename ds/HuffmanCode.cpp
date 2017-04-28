#include <stdio.h>

typedef struct {
	double weight;
	int p, l, r;
}HNode;

typedef struct {
	HNode *data;
	int n;
}HuffmanTree;


void printHuffmanNodes(HuffmanTree &htree, const int M) {
	for (int i = 1; i < M; i++) {
		printf("%d: %f %d %d %d\n", i, htree.data[i].weight, htree.data[i].p, htree.data[i].l, htree.data[i].r);
	}
	printf("\n");
}

void select_tree_root(HuffmanTree &htree, const int M, int &m1, int &m2) {
	int i = 1;
	while (htree.data[i].p != 0) i++;
	m1 = i++;
	while (htree.data[i].p != 0) i++;
	m2 = i;
	if (htree.data[m2].weight < htree.data[m1].weight) {
		int t = m1; m1 = m2; m2 = t;
	}
	i++;
	for (; i < M; i++) {
		if (htree.data[i].p != 0) continue;
		if (htree.data[i].weight < htree.data[m1].weight) {
			m2 = m1;
			m1 = i;
		}
		else if (htree.data[i].weight < htree.data[m2].weight)
			m2 = i;
	}
	return;
}
void select_tree_root_(HuffmanTree &htree, const int M, int &m1, int &m2) {
	int i = 1;
	while (htree.data[i].p != 0) i++;
	m1 = i; i++;
	double m2_value = 1e10;
	for (; i < M; i++) {
		if (htree.data[i].p != 0) continue;
		if (htree.data[i].weight < htree.data[m1].weight) {
			m2 = m1;     m2_value = htree.data[m1].weight;
			m1 = i;
		}
		else if (htree.data[i].weight < m2_value) {
			m2 = i;		 m2_value = htree.data[i].weight;
		}
	}
	return;
}
void select_tree_root__(HuffmanTree &htree, const int M, int &m1, int &m2) {
	double m1_value = 1e10, m2_value = 1e10;
	m1 = m2 = 0;
	for (int i = 1; i < M; i++) {
		if (htree.data[i].p != 0) continue;
		if (htree.data[i].weight < m1_value) {
			m2 = m1;    m2_value = m1_value;
			m1 = i;     m1_value = htree.data[m1].weight;
		}
		else if (htree.data[i].weight < m2_value) {
			m2 = i;		m2_value = htree.data[i].weight;
		}
	}
	return;
}

bool creatHuffmanTree(const double weights[], const int n, HuffmanTree &htree) {
	htree.data = new HNode[2 * n];  if (!htree.data) return false;
	htree.n = n;
	int i;
	for (i = 1; i <= n; i++) {
		htree.data[i].weight = weights[i - 1];
		htree.data[i].p = htree.data[i].l = htree.data[i].r = 0;
	}
	int n_2 = 2 * n - 1;
	for (i = n + 1; i <= n_2; i++) {
		int m1, m2;
		//	printHuffmanNodes(htree,i);
		select_tree_root_(htree, i, m1, m2);
		htree.data[i].weight = htree.data[m1].weight + htree.data[m2].weight;
		htree.data[i].l = m1; htree.data[i].r = m2;		htree.data[i].p = 0;
		htree.data[m1].p = i; htree.data[m2].p = i;
	}

	return true;
}

typedef char * HuffmanCode;
HuffmanCode * genHuffmanCode(HuffmanTree &htree) {
	HuffmanCode *codes = new HuffmanCode[htree.n];
	char *cd = new char[htree.n]; //
	for (int i = 1; i <= htree.n; i++) {
		int j = i, p, k = 0;
		while (htree.data[j].p != 0) {
			p = htree.data[j].p;
			if (htree.data[p].l == j)
				cd[k++] = '0';
			else cd[k++] = '1';

			j = p;
		}

		codes[i - 1] = new char[k + 1];
		for (j = k-1; j >=0; j--)
			codes[i - 1][k-1-j] = cd[j]; //codes[i - 1][j] = cd[j];
		codes[i - 1][k] = '\0';
	}
	delete[] cd;
	return codes;
}

void printHuffmanCode(HuffmanCode * codes, int n) {
	for (int i = 0; i < n; i++) {
		printf("%s\n", codes[i]);
	}
	printf("\n");
}

int main() {
	double weights[] = { 0.05,0.29,0.07,0.08,0.14,0.23,0.03,0.11 };
	const int n = 8;
	HuffmanTree htree;

	creatHuffmanTree(weights, n, htree);

	printHuffmanNodes(htree, 16);

	HuffmanCode * codes = genHuffmanCode(htree);

	printHuffmanCode(codes, n);
	return 0;
}