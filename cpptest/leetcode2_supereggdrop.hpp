//
// Created by yryang on 2020/4/13.
//

#ifndef CPPTEST_LEETCODE2_SUPEREGGDROP_HPP
#define CPPTEST_LEETCODE2_SUPEREGGDROP_HPP

#include <iostream>
#include <unordered_map>

using namespace std;
class Solution2 {
public:

    unordered_map<int, int> memo;
    int dp(int K, int N){
        if(memo.find(N*100+K) == memo.end()){
            int ans = INT_MAX;
            for(int i=1; i<=N; ++i){
                int t1 = dp(K, N-i);
                int t2 = dp(K-1, i-1);
                int tmp = std::max(t1, t2);
                ans = std::min(tmp, ans);
            }
            memo[N*100+K] = ans + 1;
        }
        return memo[N*100+K];
    }

    int superEggDrop(int K, int N) {
        for(int i=1; i <= N; ++i){
            memo[i*100 + 1] = i;
        }
        for(int i=1; i<=K; ++i){
            memo[100+i] = 1;
        }
        return dp(K, N);
    }
};

#endif //CPPTEST_LEETCODE2_SUPEREGGDROP_HPP
