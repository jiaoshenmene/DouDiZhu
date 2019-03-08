//
//  Tools.cpp
//  DouDiZhu-mobile
//
//  Created by 杜甲 on 2019/3/7.
//

#include "Tools.h"

void Tools::sortedForArray(std::vector<Sprite *> &valueArr,std::vector<std::string> &keyArr)
{
    size_t kcount = keyArr.size();
    for (size_t i = 0; i < kcount - 1; i++) {
        for (size_t j = kcount - 1; j > i; j--) {
            std::string key = keyArr[j];
            std::string upkey = keyArr[j - 1];
            if (key.compare(upkey) > 0) {
                std::swap(keyArr[j], keyArr[j - 1]);
                std::swap(valueArr[j], valueArr[j - 1]);
            }
        }
    }
}


