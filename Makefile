include $(TOPDIR)/rules.mk

PKG_NAME:=my-amx
PKG_RELEASE:=1

SOURCE_DIR:=~/amal/prpl/custom/my-amx

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Debug

define Package/${PKG_NAME}
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=AMX Methods Registration Utility
	DEPENDS:=+libamxo +libamxs +libamxb +libamxd +libamxrt +libamxm +libubox +libblobmsg-json +ubus
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r $(SOURCE_DIR)/* $(PKG_BUILD_DIR)/
	$(Build/Patch)
endef

define Package/${PKG_NAME}/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/${PKG_NAME} $(1)/usr/bin/${PKG_NAME}

	$(INSTALL_DIR) $(1)/etc/amx/${PKG_NAME}
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/odl/* $(1)/etc/amx/${PKG_NAME}

	$(INSTALL_DIR) $(1)/usr/lib/amx/${PKG_NAME}
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/amx/${PKG_NAME}/* $(1)/usr/lib/amx/${PKG_NAME}/

endef

$(eval $(call BuildPackage,${PKG_NAME}))
