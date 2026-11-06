#include <Geode/Geode.hpp>
#include <Geode/modify/MyStuffPopup.hpp>
#include <Geode/utils/NodeIDs.hpp>

using namespace geode::prelude;
using namespace geode::node_ids;

$register_ids(MyStuffPopup) {
    if (auto mainLayer = setIDSafe<CCLayer>(this, 0, "main-layer")) {
        auto bg = setIDSafe<CCScale9Sprite>(mainLayer, 0, "background");
        setIDSafe<CCLabelBMFont>(mainLayer, 0, "title");

        auto closeMenu = CCMenu::create();
        closeMenu->setID("close-menu");
        closeMenu->setPosition(getContentSize() / 2 + bg->getContentSize() * ccp(-0.5f, 0.5f) + ccp(4, -2));
        mainLayer->addChild(closeMenu);

        if (auto buttonsMenu = setIDSafe<CCMenu>(mainLayer, 0, "buttons-menu")) {            
            if (auto* node = buttonsMenu->getChildByTag(0))
                node->setID("youtube-button");

            if (auto* node = buttonsMenu->getChildByTag(1))
                node->setID("twitter-button");

            if (auto* node = buttonsMenu->getChildByTag(2))
                node->setID("twitch-button");

            if (auto* node = buttonsMenu->getChildByTag(3))
                node->setID("instagram-button");

            if (auto* node = buttonsMenu->getChildByTag(4))
                node->setID("tiktok-button");

            if (Ref<CCNode> node = buttonsMenu->getChildByTag(-1)) {
                node->removeFromParentAndCleanup(false);
                node->setPosition(ccp(0, 0));
                node->setID("close-button");
                closeMenu->addChild(node);
            }

            buttonsMenu->setPositionY(buttonsMenu->getPositionY() - 10);
            buttonsMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(9));
        };
    }
}

struct MyStuffPopupIDs : Modify<MyStuffPopupIDs, MyStuffPopup> {
    static void onModify(auto& self) {
        if (!self.setHookPriority("MyStuffPopup::init", GEODE_ID_PRIORITY)) {
            log::warn("Failed to set MyStuffPopup::init hook priority, node IDs may not work properly");
        }
    }

    bool init(GJUserScore* score) {
        if (!MyStuffPopup::init(score)) return false;
        NodeIDs::get()->provide(this);
        return true;
    }
};