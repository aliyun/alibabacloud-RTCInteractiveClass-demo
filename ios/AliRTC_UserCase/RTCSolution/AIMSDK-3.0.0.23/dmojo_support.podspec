Pod::Spec.new do |spec|
    spec.name         = "dmojo_support"
    spec.version      = "1.0.1.12"
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
    spec.vendored_frameworks = "libdmojo_support.framework"
  end
  