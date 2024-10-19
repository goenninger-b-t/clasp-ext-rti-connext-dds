(k:defines "RTI_UNIX")
(k:includes #~"include/rti-connext-dds/")
(k:includes #~"/Applications/rti_connext_dds-7.3.0/include/"
            #~"/Applications/rti_connext_dds-7.3.0/include/ndds/"
            #~"/Applications/rti_connext_dds-7.3.0/include/ndds/hpp/")

(k:library "nddscpp2d" :path #p"/Applications/rti_connext_dds-7.3.0/lib/arm64Darwin20clang12.0/" :kind :dynamic)

(k:recurse #p"src/" #p"include/")


;;(k:systems :rti-connext-dds)

