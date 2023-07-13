
(cl:in-package :asdf)

(defsystem "position_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "ObjectPosition" :depends-on ("_package_ObjectPosition"))
    (:file "_package_ObjectPosition" :depends-on ("_package"))
    (:file "ObjectPositions" :depends-on ("_package_ObjectPositions"))
    (:file "_package_ObjectPositions" :depends-on ("_package"))
  ))