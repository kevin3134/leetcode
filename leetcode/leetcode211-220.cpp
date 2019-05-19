#include "include.h"

#ifdef LEETCODE_211_220
#include "public.h"
#include "leetcode.h"

int Solution::getusedir_212(vector<vector<bool>> searchde_board, int predir, int prex, int prey)
{
	if (predir == 0)
		if ((prey != 0) && (!searchde_board[prey - 1][prex])) return predir;
		else return getusedir_212(searchde_board, ++predir, prex, prey);
	else if (predir == 1)
		if ((prex != searchde_board[0].size() - 1) && (!searchde_board[prey][prex + 1])) return predir;
		else return getusedir_212(searchde_board, ++predir, prex, prey);
	else if (predir == 2)
		if ((prey != searchde_board.size() - 1) && (!searchde_board[prey + 1][prex])) return predir;
		else return getusedir_212(searchde_board, ++predir, prex, prey);
	else if (predir == 3)
		if ((prex != 0) && (!searchde_board[prey][prex - 1])) return predir;
		else return getusedir_212(searchde_board, ++predir, prex, prey);
	else
		return predir;
}

vector<string> Solution::findWords(vector<vector<char>>& board, vector<string>& words)
{
	if (words.size() == 0) return vector<string>{};
	if (board.size() == 0) return vector<string>{};
	if (board[0].size() == 0) return vector<string>{};

	Trie* allwords = new Trie();
	//�������,д��������һ��
	//words��Ҫ����һ���ֵ���,ʹ��208���ǰ׺��
	for (auto word : words)
		allwords->insert(word);

	vector<string> res = {};

	//DFS,������ʼ��:
	//ά��һ��stack,�������Ի��ݵĵ�
	stack<vector<int>> st;  //ÿ���б�4��Ԫ��,�ֱ���x,y,��������һ������ĵ��Ӧ��words�±�,��һ������(0:north,1:east,2:south,3:west)

	int m = board.size();
	int n = board[0].size();
	int starty = 0;
	int startx = 0;

	//��ʼ����+DFS
	//ά��һ��searchde_board��ʾ�Ѿ��������ĵط�
	vector<vector<bool>> searchde_board(m, vector<bool>(n, false));
	//ά��һ���Ƿ���Ҫ���ݵı��
	bool isneed_recall;
	//ά��һ����ǰ�ַ����Լ���ǰ�ַ�������
	string prestr;
	int prelen;  //prelen�������û��,���ȷ�������
	int prex;
	int prey;
	int predir;      //��ǰ���÷���,�ڻ����лᶯ̬�仯
	bool isthislocend;

	while (true)
	{
		//vector<vector<bool>> searchde_board(m, vector<bool>(n, false));
		isneed_recall = false;
		//ά��һ����ǰ�ַ����Լ���ǰ�ַ�������
		prestr = "";
		prelen = 0;  //prelen�������û��,���ȷ�������
		predir = 0;      //��ǰ���÷���,�ڻ����лᶯ̬�仯
		isthislocend = false;
		prex = startx;
		prey = starty;

		while (!isthislocend)
		{
			if (!isneed_recall)
			{
				//�洢��ǰ·��/�ַ���
				string temp = prestr + board[prey][prex];

				if (allwords->search(temp))
				{
					vector<string>::iterator iter = find(res.begin(), res.end(), temp);
					if (iter == res.end())
						res.push_back(temp);
				}

				if (allwords->startsWith(temp))  //����ض����ظ�����һ��,���
				{
					//��¼�ɻ���·��(next·��)
					//��ȡʵ�ʿ��÷���
					int usedir = getusedir_212(searchde_board, predir, prex, prey);
					if (usedir <= 3)
					{
						st.push(vector<int> {prex, prey, prelen, usedir + 1});
						prelen++;
						searchde_board[prey][prex] = true;
						switch (usedir)
						{
						case 0:
						{
							prey--;
							break;
						}
						case 1:
						{
							prex++;
							break;
						}
						case 2:
						{
							prey++;
							break;
						}
						case 3:
						{
							prex--;
							break;
						}
						default:   //�����Ͼ��Բ��ᵽ����
							break;
						}
						prestr = temp;
					}
					else isneed_recall = true;
				}
				else isneed_recall = true;
			}
			else  //����
			{
				//����prex,prey,����searchde_board,����prestr,����prelen
				while (true)
				{
					if (st.empty())
					{
						isthislocend = true;
						break;
					}

					vector<int> hisinfo = st.top();
					int i_prex = hisinfo[0];
					int i_prey = hisinfo[1];
					int i_predir = hisinfo[3];
					int i_usedir = getusedir_212(searchde_board, i_predir, i_prex, i_prey);
					if (i_usedir <= 3)
					{
						prex = i_prex;
						prey = i_prey;
						st.top()[3]++;
						switch (i_usedir)
						{
						case 0:
						{
							prey--;
							break;
						}
						case 1:
						{
							prex++;
							break;
						}
						case 2:
						{
							prey++;
							break;
						}
						case 3:
						{
							prex--;
							break;
						}
						default:   //�����Ͼ��Բ��ᵽ����
							break;
						}
						isneed_recall = false;
						break;
					}
					else
					{
						searchde_board[i_prey][i_prex] = false;
						prestr.pop_back();
						prelen--;
						st.pop();
					}
				}
			}
		}

		//һ������������
		if (startx == n - 1)
		{
			if (starty == m - 1)
				break;
			else
			{
				starty++;
				startx = 0;
			}
		}
		else startx++;
	}

	return res;
}

int Solution::rob_199(vector<int>& nums, int startloc, int endloc)
{
	//dpi:͵�Կ�ͷֱ������i�±�������
//ֻ�����������dp
//init
	int nsize = endloc - startloc + 1;

	if (nsize <= 0)
		return 0;
	else if (nsize == 1)
		return nums[startloc];
	else if (nsize == 2)
		return max(nums[startloc], nums[endloc]);
	else
	{
		int dp0 = nums[startloc];
		int dp1 = nums[startloc + 1];
		int dp2 = nums[startloc] + nums[startloc + 2];
		for (int i = startloc + 3; i <= endloc; i++)
		{
			dp0 = max(dp0, dp1) + nums[i];
			int temp = dp0;
			dp0 = dp1;
			dp1 = dp2;
			dp2 = temp;
		}
		return max(dp1, dp2);
	}
}

int Solution::rob_213(vector<int>& nums)
{
	//��������198��
	if (nums.size() == 0) return 0;
	else if (nums.size() == 1) return nums[0];
	else return max(rob_199(nums, 0, nums.size() - 2), rob_199(nums, 1, nums.size() - 1));
}

string Solution::shortestPalindrome(string s)
{
	//�ҳ�������࿪ʼ������Ĵ�

	//��s�����ο�ʼ��չ,O(n^2),���м俪ʼ��չ,��
	//�����������㷨�ᳬʱ
	//��:������Ŀ5

	//Manacher algorithm
	//�ر�ע��߽�����
	//https://mp.weixin.qq.com/s?__biz=MzIzMTE1ODkyNQ==&mid=2649410225&idx=1&sn=ed045e8edc3c49a436a328e5f0f37a55&chksm=f0b60f53c7c18645b4c04a69ad314723cce94ed56994d6f963c2275a2db8d85f973f15f508e4&mpshare=1&scene=23&srcid=1001JCsBlpxgUWjgixasChNQ#rd

	string newstr = string("#");
	unsigned int iSize = s.size();
	for (unsigned int i = 0; i < iSize; i++)
	{
		newstr += s[i];
		newstr += "#";
	}

	int new_len = newstr.size();
	vector<int> radius = {};
	int right_border = -1;
	int center_index = -1;
	int longest_radius = -1;
	int longest_center_index = -1;
	for (int index = 0; index < new_len; index++)
	{
		if (index > right_border)
		{
			//expand the right border
			int L = index;
			int R = index;
			while ((L >= 0) && (R < new_len) && (newstr[L] == newstr[R]))
			{
				L--;
				R++;
			}
			int newradius = (R - L + 1) / 2;    //�˴�������ȡ��
			radius.insert(radius.end(), newradius);
			right_border = R - 1;
			center_index = index;
			if ((L == -1) && (newradius > longest_radius))
			{
				longest_radius = newradius;
				longest_center_index = index;
			}
		}
		else if ((index + radius[2 * center_index - index] - 1) >= right_border)
		{
			//also expand the right border
			int L = 2 * index - right_border;
			int R = right_border;
			while ((L >= 0) && (R < new_len) && (newstr[L] == newstr[R]))
			{
				L--;
				R++;
			}
			int newradius = (R - L + 1) / 2;    //�˴�������ȡ��
			radius.insert(radius.end(), newradius);
			right_border = R - 1;
			center_index = index;
			if ((L == -1) && (newradius > longest_radius))
			{
				longest_radius = newradius;
				longest_center_index = index;
			}
		}
		else radius.insert(radius.end(), radius[2 * center_index - index]);
	}

	float real_index = (longest_center_index + 1) / 2.0 - 1;  //may be xxx.5  4->1.5 2->0.5, 3->1, 1->0
	float real_radius = (longest_radius) / 2.0 - 1;         //5 ->1.5,  3->0.5  4->1, 2->0

	string res = s;
	for (int i = int(2 * real_radius + 1); i < s.size(); i++)
		res.insert(res.begin(), s[i]);
	return res;
}

int Solution::findKthLargest(vector<int>& nums, int k)
{
	//�۰�:��������

	vector<int> smallnums = {};  //��һ��������nums[0],<=nums[0]����Ч����Ӧ����1
	vector<int> bignums = {};

	for (auto num : nums)
	{
		if (num > nums[0])
			bignums.push_back(num);
		else
			smallnums.push_back(num);
	}
	smallnums.erase(smallnums.begin());
	if (bignums.size() == (k - 1)) return nums[0];
	else if (bignums.size() > (k - 1)) return findKthLargest(bignums, k);
	else return findKthLargest(smallnums, k - 1 - bignums.size());
}

vector<vector<int>> Solution::combinationSum3(int k, int n)
{
	//����
	vector<vector<int>> res = {};
	if ((k <= 0) || (k > 9)) return res;
	if (k == 1) return ((n <= 9) && (n >= 1)) ? vector<vector<int>> {vector<int> {n}} : res;

	unordered_map<int, pair<int, int>> um; //�����н�����ֵ����Сֵ
	um[2] = pair<int, int>{ 3,17 };
	um[3] = pair<int, int>{ 6,24 };
	um[4] = pair<int, int>{ 10,30 };
	um[5] = pair<int, int>{ 15,35 };
	um[6] = pair<int, int>{ 21,39 };
	um[7] = pair<int, int>{ 28,42 };
	um[8] = pair<int, int>{ 36,44 };
	um[9] = pair<int, int>{ 45,45 };
	if ((n > um[k].second) || (n < um[k].first)) return res;
	vector<int> pre = { 1 };
	int prelen = 1;
	int presum = 1;
	bool isneedrecall = false;

	while (true)
	{
		if (!isneedrecall)
		{
			if (prelen == (k - 1))
				if (((n - presum) > 9) || ((n - presum) < 1))
				{
					isneedrecall = true;
				}
				else if (pre[pre.size() - 1] < (n - presum))
				{
					res.push_back(pre);
					res[res.size() - 1].push_back(n - presum);
					isneedrecall = true;
				}
				else
					isneedrecall = true;
			else
			{
				if (pre[pre.size() - 1] == 9)
				{
					isneedrecall = true;
				}
				else
				{
					pre.push_back(pre[pre.size() - 1] + 1);
					prelen++;
					presum += pre[pre.size() - 1];
				}
			}
		}
		else
		{
			if (pre[pre.size() - 1] == 9)
			{
				presum -= pre[pre.size() - 1];
				pre.pop_back();
				prelen--;
				if (pre.empty()) break;
			}
			else
			{
				pre[pre.size() - 1]++;
				presum++;
				isneedrecall = false;
			}
		}
	}
	return res;
}

bool Solution::containsDuplicate(vector<int>& nums)
{
	unordered_set<int> us;
	for (auto num : nums)
		if (us.find(num) == us.end())
			us.insert(num);
		else
			return true;
	return false;
}

bool Solution::complare_218(pair<int, int> p1, pair<int, int> p2)
{
	if (p1.first < p2.first)
		return true;
	else if (p1.first > p2.first)
		return false;
	else
		if (p1.second <= p2.second)
			return true;
		else
			return false;
}

vector<vector<int>> Solution::getSkyline(vector<vector<int>>& buildings)
{
	//ά��һ�����ȶ���,�������߶�
	//��buildings��Ϣ�������·�ʽ����:����[2,9,10]����:(2,-10),(9,10)��ʾ��2����10���9�½�10
	//������Щ��,���յ�һ:pos���򡢵ڶ�height��������(height�����и�,�����������½��ķ���ͬ����ͬ),Ȼ�����Щ�㰴���������ȼ�����,����ܹ��������߶�(��������(����)һ�����߶Ȼ���ɾ��(�½�)һ�����߶�),��ô��¼��ǰ���߶��뵱ǰλ��,���򲻲���

	vector<vector<int>> res = {};
	if (buildings.size() == 0) return res;

	//ʹ��multiset:�ɺ��ظ�Ԫ�صļ���(��֤����)

	multiset<pair<int, int>, less<pair<int, int>>> points;   //��¼λ��,�߶�(�������ŵ�),��������,С�±��ֵС�ڴ��±��
	multiset<int, greater<int>> maxheights = { 0 }; //ֵ���Ԫ����С���±괦,��һ��0ȷ����multiset��Ϊ��

	for (auto building : buildings)
	{
		points.insert(pair<int, int> {building[0], -1 * building[2]});
		points.insert(pair<int, int> {building[1], building[2]});
	}

	int hisheight = 0;
	for (auto point : points)
	{
		if (point.second < 0) //��¥��ʼ����,�߶�����
			maxheights.insert(-1 * point.second);
		else                 //��¥��ʼ����,�߶��½�,���õ���erase��ָ��λ��,��Ϊ�㷨��������һ����Ԫ�ر��Ƴ�
			maxheights.erase(maxheights.find(point.second));
		multiset<int, greater<int>>::iterator it = maxheights.begin();
		if (hisheight != *it)   //ע:����������ʲô����it�޷����ַ����,��ôһ�������FUCK multiset����
			res.push_back(vector<int> {point.first, *it});
		hisheight = *it;
	}

	return res;
}

bool Solution::containsNearbyDuplicate(vector<int>& nums, int k)
{
	unordered_map<int, int> um;
	for (int i = 0; i < nums.size(); i++)
	{
		if (um.find(nums[i]) == um.end())
			um[nums[i]] = i;
		else
			if ((i - um[nums[i]]) <= k) return true;
			else um[nums[i]] = i;
	}
	return false;
}

bool Solution::containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{



	//ά��һ��vector
	//������� O(n^2)
	//���TIE
	/*
	if (k < 1) return false;
	if (t < 0) return false;

	vector<int> q;

	for (int i = 0; i < nums.size(); i++)
	{
		for (auto val : q)
		{
			if (abs((long)val - nums[i]) <= t) return true;
		}
		if (q.size() == k)
		{
			q.erase(q.begin());
		}
		q.push_back(nums[i]);
	}
	return false;*/

	//��һ�ֱ������,�Ȱ�ֵ����,ͬʱ��¼�����Ķ�Ӧ�±�
	//O(n^2)
	if (k < 1) return false;
	if (t < 0) return false;

	vector<pair<int, int>> vp(nums.size(), pair<int, int> {});
	for (int i = 0; i < nums.size(); ++i)
		vp[i] = pair<int, int>{ nums[i],i };

	sort(vp.begin(), vp.end()); //�Զ�����pair<int,int> val.first��������

	int j = 0;
	for (int i = 1; i < nums.size(); i++)
	{
		while ((j < i) && ((vp[j].first + t) < vp[i].first))
			j++;
		for (int m = j; m < i; m++)
			if (abs(vp[m].second - vp[i].second) <= k)
				return true;
	}
	return false;



}

#else
#endif