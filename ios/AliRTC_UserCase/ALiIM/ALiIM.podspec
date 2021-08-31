#
# Be sure to run `pod lib lint ALiIM.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'ALiIM'
  s.version          = '0.1.0'
  s.summary          = 'A short description of ALiIM.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/aliyunvideo/ALiIM'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'aliyunvideo' => '' }
  s.source           = { :git => '', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'

#  s.source_files = 'ALiIM/**/*.{h,m}'
  
   # s.resources  = 'ALiIM/ALiIM.bundle','ALiIM/*.storyboard'
  
  s.pod_target_xcconfig = { 'ENABLE_BITCODE' => 'NO' }
  

  s.subspec 'AIM' do |ss|

    ss.source_files = 'ALiIM/**/*.{h,m}'

    ss.ios.dependency 'libdps'
    ss.ios.dependency 'OpenSSL'
    ss.ios.dependency 'xlite'
    ss.ios.dependency 'gaea'
    ss.ios.dependency 'dmojo_support'
    ss.ios.dependency 'libaim'
    
#    ss.ios.dependency 'dps4ios', '3.0.0.18-SNAPSHOT' # DingPaaS基座SDK
#    ss.ios.dependency 'BabaSSL' , '1.1.1-h.c09a949f-2' # 钉钉定制版sqlite
#    ss.ios.dependency 'xlite', '1.0.2.9' # OpenSSL 1.1.1
#    ss.ios.dependency 'GaeaNetwork' , '2.0.0.8' # 钉钉网络库
#    ss.ios.dependency 'DmojoSupport4ios' , '1.0.1.12' # DingPaaS OC绑定框架
#    ss.ios.dependency 'DingPaaSAIM4ios' , '3.0.0.21-SNAPSHOT' # IM SDK

    ss.ios.dependency  'Masonry'

  end

end
