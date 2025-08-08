include $(TOPDIR)/rules.mk

PKG_NAME:=my-amx
PKG_RELEASE:=1

SOURCE_DIR:=$(HOME)/amal/prpl/custom/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Debug

define Package/$(PKG_NAME)
	CATEGORY:=Examples
	SECTION:=utils
	TITLE:=AMX Methods Registration Utility
	DEPENDS:= libamxo libamxs libamxb libamxd
	DEPENDS+= libamxrt libamxm libubox libblobmsg-json libubus
	DEPENDS+= libsahtrace
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r $(SOURCE_DIR)/* $(PKG_BUILD_DIR)/
	$(Build/Patch)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)
	$(CP) -a $(PKG_INSTALL_DIR)/* $(1)/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

