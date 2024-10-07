//#include<iostream>
//#include<queue>
//#include<vector>
//
//using std::vector;
//using std::queue;
//
//class Solution {
//public:
//    int timeRequiredToBuy(vector<int>& tickets, int k) {
//        int time = 0;
//        int len = tickets.size();
//        queue<int> Queue;
//        for (int i = 0; i < len; ++i) {
//            Queue.push(tickets[i]);
//        }
//        while (!Queue.empty()) {
//            static int i = 0;
//            if (tickets[i % len] > 0) {
//                --tickets[i % len];
//                ++time;
//                if (tickets[i % len] > 0) {
//                    Queue.pop();
//                    Queue.push(tickets[i % len]);
//                }
//                else {
//                    Queue.pop();
//                }
//            }
//            ++i;
//            if (tickets[k] == 0) break;
//        }
//        return time;
//    }
//};
//
//class Solution1 {
//public:
//    int timeRequiredToBuy(vector<int>& tickets, int k) {
//        int n = tickets.size();
//        int res = 0;
//        for (int i = 0; i < n; ++i) {
//            if (i <= k) {
//                res += std::min(tickets[i], tickets[k]);
//            }
//            else {
//                res += std::min(tickets[i], tickets[k] - 1);
//            }
//        }
//        return res;
//    }
//};
//
//int main(void) {
//
//
//    vector<int> res{ 84,49,5,24,70,77,87,8 };
//    vector<int> r{ 84,49,5,24,70,77,87,8 };
//
//    Solution sol;
//    Solution1 fs;
//
//    std::cout << sol.timeRequiredToBuy(res, 3) << std::endl;
//    std::cout << fs.timeRequiredToBuy(r, 3) << std::endl;
//
//     
//
//	return 0;
//}
//
//
