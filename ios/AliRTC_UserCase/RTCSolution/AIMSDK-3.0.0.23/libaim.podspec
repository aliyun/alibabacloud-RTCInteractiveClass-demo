Pod::Spec.new do |s|
    s.name         = "libaim"
    s.version      = "3.0.0.23"
    s.summary      = "libaim"
  
    s.description  = <<-DESC
                     aim sdk description
                     DESC
  
    s.homepage     = "http://gitlab.alibaba-inc.com/DingTalk-Ship/ark"
    s.license      = {
      :type => 'Copyright',
      :text => <<-LICENSE
             Alibaba-INC copyright
      LICENSE
    }
    s.authors      = { "dingyuan" => "miaoqing.wmq@alibaba-inc.com" }
    s.platform     = :ios, "8.0"
    s.source       = { :git => "git@gitlab.alibaba-inc.com:DingTalk-Ship/ark.git", :tag => "#{s.version}" }
    
    s.source_files = 'libaim.framework/Versions/A/Headers/*.h'
    s.requires_arc = true
    s.vendored_frameworks = "libaim.framework"
  end