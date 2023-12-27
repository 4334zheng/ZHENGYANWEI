import requests
# 调用python中解析XML的类库ElementTree加载得到xml文本
import xml.etree.ElementTree as ET
# 编写对每个接口调用的代码

# 无参数的get请求
def get_region_country_get():
      # 将url设置为接口的网址
      url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx/getRegionCountry"
      # 由于该接口不需要进行传参，所以只把url传入
      resp = requests.get(url=url)
      # check the status code
      assert resp.status_code == 200
      text = resp.text
      root = ET.fromstring(text)
      # get the top
      country = root.find('{http://WebXml.com.cn/}string').text
      print(country)
      assert country == '阿尔及利亚,3320'

      # get all
      countries = root.findall('{http://WebXml.com.cn/}string')
      for country in countries:
          print(country.text)

      # check the length of the countries
      assert len(countries) == 79
      print(resp.text)

# 带参数的GET的请求
def get_support_city_string_get():
      url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx/getSupportCityString"
      # 根据接口要求，这里要传入地区编码，而地区编码可以通过getRegionProvince接口获得
      resp = requests.get(url=url, params={"theRegionCode": "3113"})
      assert resp.status_code == 200
      text = resp.text
      root = ET.fromstring(text)

      # get the top
      city = root.find('{http://WebXml.com.cn/}string').text
      assert city == '阿城,120'

      # get all
      cities = root.findall('{http://WebXml.com.cn/}string')
      for city in cities:
          print(city.text)
      assert len(cities) == 82
      print(resp.text)

# c带正文（正文格式为application/x-www-form-urlencoded ）的POST请求
def get_support_city_string_post():
      url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx/getSupportCityString"
      resp = requests.post(url=url,
                           headers={"Content-Type": "application/x-www-form-urlencoded"},
                           data={"theRegionCode": "3114"})
      assert resp.status_code == 200
      text = resp.text
      root = ET.fromstring(text)

      # get the top
      city = root.find('{http://WebXml.com.cn/}string').text
      print(city)
      assert city == '安图,658'

      # get all
      cities = root.findall('{http://WebXml.com.cn/}string')
      for city in cities:
          print(city.text)

      assert len(cities) == 50
      print(resp.text)

# d带正文（正文格式为 xml的）的POST请求
def get_support_city_string_post_xml():
      url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx"
      data = '''<?xml version="1.0" encoding="utf-8"?>
            <soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
            <soap:Body>
            <getSupportCityString xmlns="http://WebXml.com.cn/">
            <theRegionCode>3115</theRegionCode>
            </getSupportCityString>
            </soap:Body>
            </soap:Envelope> '''
      resp = requests.post(url=url,
                        data=data,
                        headers={'Content-Type': 'text/xml'}
                        )

      assert resp.status_code == 200
      text = resp.text
      namespaces = {
                  'soap': 'http://schemas.xmlsoap.org/soap/envelope/',
                  'a': 'http://WebXml.com.cn/',
                  }
      root = ET.fromstring(text)

      # 获取City的头节点
      city = root.find('./soap:Body'
                        '/a:getSupportCityStringResponse'
                        '/a:getSupportCityStringResult'
                        '/a:string',
                        namespaces).text
      assert city == '鞍山,724'

      # 找到全部City
      cities = root.findall('./soap:Body'
                        '/a:getSupportCityStringResponse'
                        '/a:getSupportCityStringResult'
                        '/a:string',
                        namespaces)
      for city in cities:
            print(city.text)
      assert len(cities) == 55
      print(resp.text)

# e不带正文的POST请求
def get_region_province_post():
      url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx/getRegionProvince"
      resp = requests.post(url=url)

      assert resp.status_code == 200
      text = resp.text
      root = ET.fromstring(text)

      # get the top
      province = root.find('{http://WebXml.com.cn/}string').text
      print(province)
      assert province == '黑龙江,3113'

      # get all
      provinces = root.findall('{http://WebXml.com.cn/}string')
      for province in provinces:
            print(province.text)

      assert len(provinces) == 35
      print(resp.text)

if __name__ == '__main__':
      #get_region_country_get()
      #get_support_city_string_get()
      get_support_city_string_post()
      #get_support_city_string_post_xml()
      #get_region_province_post()