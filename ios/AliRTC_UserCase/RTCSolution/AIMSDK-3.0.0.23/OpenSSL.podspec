Pod::Spec.new do |spec|
    spec.name         = "OpenSSL"
    spec.version      = "1.1.1"
    spec.summary      = "OpenSSL is an SSL/TLS and Crypto toolkit. Deprecated in Mac OS and gone in iOS, this spec gives your project non-deprecated OpenSSL support."
    spec.description  = <<-DESC
    Alibaba DingTalk PaaS Base SDK
                     DESC
    spec.homepage     = "http://help.aliyun.com"
    spec.license      = {
      :type => 'Copyright',
      :text => <<-LICENSE
      BSD-style Open Source
      LICENSE
    }
    spec.author             = { "guangzhen.lgz" => "guangzhen.lgz@alibaba-inc.com" }
    spec.source       = { :git => "http://help.aliyun.com", :tag => "#{spec.version}" }
    spec.vendored_libraries = "OpenSSL.library/lib/libcrypto.a", "OpenSSL.library/lib/libssl.a"
  end
  