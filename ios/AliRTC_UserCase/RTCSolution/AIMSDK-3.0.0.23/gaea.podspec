Pod::Spec.new do |spec|
    spec.name         = "gaea"
    spec.version      = "2.1.0.2"
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
    spec.vendored_frameworks = "Gaea.framework"
  end
  