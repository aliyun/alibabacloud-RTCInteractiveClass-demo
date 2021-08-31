#
# Be sure to run `pod lib lint RTCInteractiveLiveClass.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
    s.name             = 'RTCInteractiveLiveClass'
    s.version          = '0.1.0'
    s.summary          = 'A short description of RTCInteractiveLiveClass.'
    
    # This description is used to generate tags and improve search results.
    #   * Think: What does it do? Why did you write it? What is the focus?
    #   * Try to keep it short, snappy and to the point.
    #   * Write the description between the DESC delimiters below.
    #   * Finally, don't worry about the indent, CocoaPods strips it!
    
    s.description      = <<-DESC
    TODO: Add long description of the pod here.
    DESC
    
    s.homepage         = 'https://github.com/aliyunvideo/RTCInteractiveLiveClass'
    # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
    s.license          = { :type => 'MIT', :file => 'LICENSE' }
    s.author           = { 'aliyunvideo' => '' }
    s.source           = { :git => '', :tag => s.version.to_s }
    # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'
    
    s.ios.deployment_target = '9.0'
    s.osx.deployment_target = '10.10'
    
   
  
    s.pod_target_xcconfig = { 'ENABLE_BITCODE' => 'NO' }
    
    s.dependency 'AliRTCSdk'
#    s.dependency 'AliPlayerSDK_iOS','4.7.5'
    s.dependency  'RTCCommon'
 
    s.subspec 'iOS' do |ss|
      ss.ios.deployment_target='9.0'
      
      ss.ios.source_files = 'RTCInteractiveLiveClass/**/*.{h,m,mm,xib}'
      ss.ios.exclude_files = 'RTCInteractiveLiveClass/osx'
      ss.ios.resources  = 'RTCInteractiveLiveClass/RTCInteractiveLiveClass.bundle','RTCInteractiveLiveClass/*.storyboard'
      

      ss.ios.dependency  'RTCCommonView' , '~>0.1.0'
      
      ss.ios.dependency  'ALiIM'

    end
    
    s.subspec 'MAC' do |ss|
      ss.osx.deployment_target = '10.10'
      ss.osx.resources = 'RTCInteractiveLiveClass/osx/*.storyboard'
      ss.osx.source_files = 'RTCInteractiveLiveClass/Manager/*.{h,m,mm}','RTCInteractiveLiveClass/osx/**/*.{h,m,mm}'
#      ss.dependency  'RTCCommonView' , '~>0.1.0'
    end
  
    s.default_subspecs = 'iOS'
end
