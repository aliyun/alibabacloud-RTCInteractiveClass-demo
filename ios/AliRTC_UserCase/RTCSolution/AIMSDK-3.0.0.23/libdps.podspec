Pod::Spec.new do |spec|
  spec.name         = "libdps"
  spec.version      = "3.0.0.20"
  spec.summary      = "DingTalk PaaS Base."
  spec.description  = <<-DESC
  Alibaba DingTalk PaaS Base SDK
                   DESC
  spec.homepage     = "http://help.aliyun.com"
  spec.license      = {
    :type => 'Copyright',
    :text => <<-LICENSE
           Alibaba-INC copyright
    LICENSE
  }
  spec.author             = { "guangzhen.lgz" => "guangzhen.lgz@alibaba-inc.com" }
  spec.source       = { :git => "http://help.aliyun.com", :tag => "#{spec.version}" }
  spec.vendored_frameworks = "libdps.framework"
  spec.libraries = "c++", "z", "resolv"
  spec.framework    = 'SystemConfiguration', 'CoreTelephony'
  spec.source_files = 'libdps.framework/Versions/A/Headers/*.h'
end
