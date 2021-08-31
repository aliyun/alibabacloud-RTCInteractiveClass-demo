#
# Be sure to run `pod lib lint RTCCommonView.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'RTCCommonView'
  s.version          = '0.1.0'
  s.summary          = 'A short description of RTCCommonView.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/aliyunvideo/RTCCommonView'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'aliyunvideo' => '' }
  s.source           = { :git => '', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'
  s.osx.deployment_target = '10.10'
  
  s.source_files = '*.h'
  
  s.ios.resources  = 'Resources/*.bundle','Resources/*.storyboard'
 
  s.subspec 'Alert' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.source_files = 'Alert/*.{h,m}'
  end

  s.subspec 'CodeView' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.source_files = 'CodeView/*.{h,m}'
  end

  s.subspec 'HUD' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.ios.source_files = 'HUD/*.{h,m}'
  end
  
  s.subspec 'LoadingButton' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.source_files = 'LoadingButton/*.{h,m}'
  end

  s.subspec 'OffLine' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.source_files = 'OffLine/*.{h,m}'
  end

  s.subspec 'Utils' do |ss|
    ss.ios.deployment_target = '9.0'
    ss.source_files = 'Utils/*.{h,m}'
  end

  s.dependency 'RTCCommon'

end
