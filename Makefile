include $(TOPDIR)/rules.mk

PKG_NAME:=my-amx
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/${PKG_NAME}
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=AMX Methods Registration Utility
	DEPENDS:=+libamxo +libamxs +libamxb +libamxd +libamxrt +libubox +libblobmsg-json +ubus
endef

define Package/${PKG_NAME}/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/${PKG_NAME} $(1)/usr/bin/${PKG_NAME}

	$(INSTALL_DIR) $(1)/etc/amx/my-amx/odl
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/odl/* $(1)/etc/amx/my-amx/odl/

	$(INSTALL_DIR) $(1)/usr/lib/amx/my-amx
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/libmy-amxl.so $(1)/usr/lib/amx/my-amx/my-amx.so

endef

$(eval $(call BuildPackage,${PKG_NAME}))
