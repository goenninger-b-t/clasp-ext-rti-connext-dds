(asdf:defsystem #:rti-connext-dds
  :description "Expose RTI Connext DDS to clasp."
  :author "Frank Gönninger <frank.goenninger@goenninger.net>"
  :maintainer "Gönninger B&T GmbH, Germany <support@goenninger.net>"
  :license  "Proprietary. All Rights Reserved. See file LICENSE.TXT for more info."
  :version "0.0.1"
  :serial t
  :depends-on (:closer-mop)
  :components ((:module rti-connext-dds
                :pathname "src/lisp/"
                :components
                ((:file "packages")
                 (:file "rti-connext-dds")))))
