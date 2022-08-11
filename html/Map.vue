<template>
  <div>
    <div id="main" style="width: 100vw;height: 100vh" />

    <!-- 弹出框的结构 -->
    <div id="tip" style="">
      <span>是否同意请求？</span>
      <div>
        <button class="btn">确定</button>
        <button class="btn">取消</button>
      </div>
    </div>

  </div>

</template>
<script>
// import map from '@/assets/json/maptest.json'
// import * as echarts from 'echarts'

// import $ from 'jquery'
var myChart = null
// const colors = ['#37A2DA', '#32C5E9', '#67E0E3', '#9FE6B8', '#FFDB5C', '#ff9f7f', '#fb7293', '#E062AE', '#E690D1', '#e7bcf3', '#9d96f5', '#8378EA', '#96BFFF']
var colorList = [
  '#C1232B', '#B5C334', '#FCCE10', '#E87C25', '#27727B',
  '#FE8463', '#9BCA63', '#FAD860', '#60C0DD',
  '#D7504B', '#C6E579', '#F4E001', '#F0805A', '#26C0C0'
]
// var tip = document.getElementById('tip')
// var btns = [...document.getElementsByClassName('btn')]
export default {
  props: {
    mapData: Object,
    truckproduceData: Object,
    shovelproduceData: Object
    // path: Array
  },
  data() {
    return {
      angles: [0],
      allendpoints: ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'a', 'b', 'c'],
      driverdemand: [[1, '请求换班'], [2, '请求加油']], // 测试 [[]]
      delData: [], // 保存将要删除的数据
      truckwithdemandData: {
        truckIdList: [],
        truckproduceIndexList: [], // 在truckproduceData中的索引
        truckLocationList: []
      }
    }
  },
  watch: {
    mapData: {
      handler(newValue, oldValue) {
        if (oldValue !== newValue) {
          this.mapData = newValue
          this.setOptions()
        }
      },
      deep: true
    },
    truckproduceData: {
      handler(newValue, oldValue) {
        if (oldValue !== newValue) {
          this.truckproduceData = newValue
          this.getAngles(newValue, oldValue)
          this.getDriverDemand()
          this.setOptions()
        }
      },
      deep: true
    },
    shovelproduceData: {
      handler(newValue, oldValue) {
        if (oldValue !== newValue) {
          this.shovelproduceData = newValue
          this.setOptions()
        }
      },
      deep: true
    },
    driverdemand: {
      handler(newValue, oldValue) {
        if (oldValue !== newValue) {
          this.driverdemand = newValue
          this.getDriverDemand()
          this.setOptions()
        }
      },
      deep: true
    }
  },
  created() {
  },
  mounted() {
    this.getDriverDemand()
    this.initChart()
  },
  methods: {
    getDriverDemand() {
      this.truckwithdemandData = {
        truckIdList: [],
        truckproduceIndexList: [], // 在truckproduceData中的索引
        truckLocationList: []
      }
      for (let i = 0; i < this.driverdemand.length; i++) {
        for (let j = 0; j < this.truckproduceData.truckIdList.length; j++) {
          if (this.driverdemand[i][0] === this.truckproduceData.truckIdList[j]) {
            this.truckwithdemandData.truckIdList.push(this.truckproduceData.truckIdList[j])
            this.truckwithdemandData.truckLocationList.push(this.truckproduceData.truckLocationList[j])
            this.truckwithdemandData.truckproduceIndexList.push(j)
          }
        }
      }
    },
    initChart() {
      var map = document.getElementById('main')
      //   var myChart = echarts.init(chartDom);
      myChart = this.$echarts.init(map)
      this.setOptions()
    },
    setOptions() {
      var option
      // 首先向 echarts 注册 SVG 字符串或解析过的 SVG DOM
      this.$echarts.registerMap('map', this.mapData)
      option = {
        backgroundColor: 'rgba(0,0,59)',
        // rgb(0,0,59)
        tooltip: {
        },
        geo: {
          map: 'map',
          roam: true,
          layoutCenter: ['50%', '50%'],
          layoutSize: '90%',
          // label: { show: true },
          // zoom: 1,
          regions: [
            {
              name: this.allendpoints[0],
              label: { show: true },
              itemStyle: {
                areaColor: colorList[0],
                borderColor: 'rgb(26,250,41)',
                borderWidth: 1
              }
            }
          ],
          itemStyle: {
            normal: {
              areaColor: '#99CBF9', // 地图区域的颜色（没有数据时会按照这个颜色显示）
              borderType: 'solid',
              borderColor: 'rgb(2,125,180)',
              borderWidth: 6
            }
          }
        },
        // grid: {
        //   top: 0,
        //   bottom: 0
        // },
        toolbox: { // 配置工具箱组件
          show: true, // 设置是否显示工具箱组件
          orient: 'horizontal', // 设置布局方式，默认为水平布局，可选:'horizontal'¦'vertical'
          // 设置水平安放位置，默认为右对齐；
          // 可选:'center'¦'left'¦'right'¦{number}（x坐标，单位px）
          x: 'center',
          // y: 'top',
          top: '105px',
          itemSize: '20', // 工具栏 icon 的大小
          color: ['#1e90ff', '#22bb22', '#4b0082', '#d2691e'],
          backgroundColor: 'rgba(0,0,0,0)', // 设置工具箱背景颜色
          borderColor: '#ccc', // 设置工具箱边框颜色
          borderWidth: 0, // 设置工具箱边框线宽，单位px,默认为0（无边框）
          padding: 5, // 设置工具箱内边距，单位px，默认各方向内边距为5
          showTitle: true,
          feature: {
            mark: { // 设置标记
              show: true,
              title: {
                mark: '辅助线-开关',
                markUndo: '辅助线-删除',
                markClear: '辅助线-清空'
              },
              lineStyle: { width: 1, color: '#1e90ff', type: 'dashed' }
            },
            restore: { // 设置数据重置
              show: true, title: '还原', color: 'black'
            },
            saveAsImage: { // 设置导出图片
              show: true, title: '保存为图片',
              type: 'jpeg', lang: ['单击本地保存']
            },
            myTool: { // 设置自定义工具按钮
              show: true, title: '自定义扩展方法',
              // 设置改变默认的图标为一个特定的图标
              // icon: 'image://../images/girl3.gif',

              icon: 'path://M733.549304 0l116.434359 116.23452-226.402521 226.40252 57.053835 57.068109 226.459617-226.445342 120.616689 120.41685V0H733.549304zM689.513507 619.855586l-57.068108 57.068109 224.232847 224.232847-122.64362 122.843458h293.676657V729.838022l-114.007751 114.207588-224.190025-224.190024zM338.197775 404.144414l57.068109-57.068109L171.033037 122.843458 293.676657 0H0v294.161978l114.022025-114.207588 224.17575 224.190024zM347.076305 624.294851L120.616689 850.754468 0 730.323343v293.676657h294.161978l-116.420084-116.23452 226.40252-226.40252-57.068109-57.068109z',
              onclick: (e) => {
                // this.$refs.echartFull.show('', e.getOption(), 'truckInfo')
                var bigger = document.getElementById('truckInfochart')
                console.log(bigger.style.width)
                bigger.style.width = 600 + 'px'
                console.log(bigger.style.width)
              }
            }
          }
        },
        series: [
          {
            name: 'truck',
            type: 'scatter',
            coordinateSystem: 'geo', // 使用地理坐标系
            data: this.truckproduceData.truckLocationList,
            symbol: 'path://M87.1667 3.8333L80.5.5h-60l-6.6667 3.3333L.5 70.5v130l10 10h80l10 -10v-130zM15.5 190.5l15 -20h40l15 20zm75 -65l-15 5v35l15 15zm-80 0l15 5v35l-15 15zm65 0l15 -5v-40l-15 20zm-50 0l-15 -5v-40l15 20zm 65,-55 -15,25 c -15,-5 -35,-5 -50,0 l -15,-25 c 25,-15 55,-15 80,0 z',

            symbolSize: [12, 28], // 散点大小
            symbolRotate: (value, params) => {
              params.symbolRotate = this.angles[params.dataIndex]
              return params.symbolRotate
            },
            cursor: 'pointer', // 鼠标悬浮时在图形元素上时鼠标的样式是什么。同 CSS 的 cursor。
            itemStyle: {
              color: (params) => {
                const truckproduceData = this.truckproduceData
                const allendpoints = this.allendpoints
                for (let i = 0; i < allendpoints.length; i++) {
                  // console.log('i')
                  // console.log(allendpoints[i])
                  // console.log(truckproduceData.endPointList[params.dataIndex])

                  if (allendpoints[i] === truckproduceData.endPointList[params.dataIndex]) {
                    return colorList[i]
                  }
                }
              }
            },
            label: {
              show: true,
              position: 'inside',
              formatter: (params) => {
                return this.truckproduceData.truckNameList[params.dataIndex]
              }
            },

            tooltip: {
              triggerOn: 'mousemove',
              enterable: true, // 设置鼠标能进入
              backgroundColor: 'rgba(255,255,255,0.7)',
              // position: function(point, params, dom, rect, size) {
              //   // 固定在顶部
              //   return [point[0], '10%']
              // },
              formatter: (params) => { // 使用箭头函数指向this!!!!!!
                // prettier-ignore
                const truckproduceData = this.truckproduceData
                return '<div style="border-bottom: 1px solid rgba(255,255,255,.3); font-size: 18px;padding-bottom: 7px;margin-bottom: 7px">' + '矿卡' +
                truckproduceData.truckNameList[params.dataIndex] + '<br>' +
                '</div>' +
                '司机' + '：' + this.truckproduceData.driverNameList[params.dataIndex] + '<br>' +
                '装载量' + '：' + this.truckproduceData.loadCapacityList[params.dataIndex] + '吨' + '<br>' +
                '品位' + '：' + this.truckproduceData.truckGradeList[params.dataIndex] + '<br>' +
                '起点' + '：' + this.truckproduceData.startPointList[params.dataIndex] + '<br>' +
                '终点' + '：' + this.truckproduceData.endPointList[params.dataIndex] + '<br>' +
                '剩余距离' + '：' + parseInt(this.truckproduceData.distanceNoList[params.dataIndex]) + '米' + '<br>' +
                // '当前位置' + ':' + '<br>' + params.data + '<br>' +
                '状态' + '：' + this.truckproduceData.truckStateList[params.dataIndex] + '<br>' +
                '当前进度' + '：' + parseInt(this.truckproduceData.curProgressList[params.dataIndex] * 100) + '%' + '<br>'
              }
            },
            animation: false
          },
          {
            name: 'shovel',
            type: 'scatter',
            coordinateSystem: 'geo', // 使用地理坐标系
            data: this.shovelproduceData.shovelLocationList,
            symbol: 'path://M100.951303 505.518987A85.701862 85.701862 0 0 0 15.249442 591.220849v116.963217a26.076545 26.076545 0 0 0 26.076545 26.076545h811.27029a32.023827 32.023827 0 0 0 31.871333-32.023828v-13.724497s-182.993299 0-396.48548-182.993299zM1744.231124 27.144006a82.499479 82.499479 0 0 0-110.710945 24.246612l-49.865674 72.892331H1067.460908c-228.741623 0-320.238273 137.244974-320.238272 137.244974l-45.748325 60.997766h99.731348s22.264185 0 37.513626 30.498883c8.692182 17.536858 17.536858 34.921221 23.331646 46.663291A373.00134 373.00134 0 0 1 1082.71035 276.777364l438.421444-60.997766L1272.413403 579.478779a40.716009 40.716009 0 0 0 63.89516 50.170663l426.984363-477.307521a82.499479 82.499479 0 0 0-19.061802-125.197915z M785.34624 360.649293h-147.309606A20.434252 20.434252 0 0 0 617.602383 381.236039v147.309605a21.806701 21.806701 0 0 0 9.912137 18.146836 745.240208 745.240208 0 0 0 198.24274 85.396872 22.11169 22.11169 0 0 0 4.422338 0 16.316902 16.316902 0 0 0 15.249441-15.249441v-81.279524a373.916307 373.916307 0 0 0-43.003425-164.541474 20.281757 20.281757 0 0 0-17.079374-10.36962z m45.748324 255.885629h-0.914966A726.330901 726.330901 0 0 1 635.749218 533.730454a5.947282 5.947282 0 0 1-2.897394-5.18481V381.236039a5.18481 5.18481 0 0 1 5.18481-5.18481h147.309606a5.18481 5.18481 0 0 1 4.727327 2.592405 358.514371 358.514371 0 0 1 41.020997 157.374236zM76.247208 902.004468a76.247208 76.247208 0 0 0 76.247207 76.247207h762.472078a76.247208 76.247208 0 0 0 0-152.494415H152.494415a76.247208 76.247208 0 0 0-76.247207 76.247208z m838.719285-60.997767a60.997766 60.997766 0 1 1-60.997766 60.997767 60.997766 60.997766 0 0 1 60.997766-60.997767z m-45.748325 0a76.247208 76.247208 0 0 0 0 121.995533H198.24274a76.247208 76.247208 0 0 0 0-121.995533z m-655.725986 60.997767a60.997766 60.997766 0 1 1-60.997767-60.997767 60.997766 60.997766 0 0 1 60.997767 60.997767z M1798.519136 83.261951a97.901415 97.901415 0 0 0-164.38898-56.117945L1143.708116 109.033507h-76.247208c-234.231422 0-328.930454 138.15994-332.437825 143.344751l-41.173493 54.897989H527.783172a42.240953 42.240953 0 0 0-41.78347 38.428593l-12.047059 144.564706H100.951303A101.103797 101.103797 0 0 0 0 591.220849v116.963217a41.325987 41.325987 0 0 0 41.325987 41.325986H304.988831l-22.874162 30.498883H152.494415a121.995532 121.995532 0 0 0 0 243.991065h762.472078a121.995532 121.995532 0 0 0 0-243.991065H724.348474l-22.874163-30.498883h151.121966a47.273269 47.273269 0 0 0 47.120774-47.273269v-166.218913a422.71452 422.71452 0 0 0-20.434251-132.212658 355.921966 355.921966 0 0 1 205.562472-111.778406l404.262695-56.117945L1265.703649 564.229337l-137.244974-82.041995v-34.311244a45.748325 45.748325 0 0 0-25.161579-40.563514l-17.841847-8.997171a33.548771 33.548771 0 0 0-48.493224 30.498883v184.06076c4.117349 98.053909 58.862844 128.247803 104.001192 136.330007a236.061355 236.061355 0 0 0 30.498883 3.812361h8.692181a157.984214 157.984214 0 0 0 143.64974-94.851527l1.219955-3.202382a55.812956 55.812956 0 0 0 22.416679-15.249442l426.984364-477.155026a98.053909 98.053909 0 0 0 24.094117-79.297096zM1619.185704 45.748325l-43.613403 63.89516H1235.204765zM914.966493 810.507818a91.496649 91.496649 0 0 1 0 182.993299H152.494415a91.496649 91.496649 0 1 1 0-182.993299z m-594.72822-30.498883l22.874162-30.498883h320.238272l22.874163 30.498883z m532.358004-60.997766H41.325987a10.827103 10.827103 0 0 1-10.827104-10.827103v-116.963217a70.45242 70.45242 0 0 1 70.45242-70.45242h381.236039C663.045719 673.872822 820.419955 698.881906 869.218168 702.846761a16.621891 16.621891 0 0 1-16.621891 16.164408zM869.218168 672.195383c-46.815786-4.727327-196.412807-30.498883-365.986597-173.38615l12.504542-150.511988a11.437081 11.437081 0 0 1 11.437081-10.522115h277.082353a18.451824 18.451824 0 0 1 15.249442 8.692182A369.493969 369.493969 0 0 1 869.218168 536.01787z m210.899777-410.362472a383.675949 383.675949 0 0 0-213.492182 110.405957 366.901564 366.901564 0 0 0-20.434251-41.020998 48.645719 48.645719 0 0 0-42.393448-23.941623H731.973194l27.906478-37.208637c0.914966-1.37245 90.429188-130.53522 307.581236-130.53522h523.513329a25.466567 25.466567 0 0 1 3.507371 50.780641zM1174.206999 722.671035a243.991065 243.991065 0 0 1-27.144006-3.354877c-50.628146-9.149665-76.247208-44.22338-78.992107-106.746091V428.204319a2.592405 2.592405 0 0 1 1.37245-2.439911 2.897394 2.897394 0 0 1 2.897394 0l17.994341 8.997171a15.249442 15.249442 0 0 1 8.234698 13.267014v51.085629l153.409382 91.496649a55.812956 55.812956 0 0 0 21.044229 56.880417 54.593001 54.593001 0 0 0 18.146836 8.997171A126.722859 126.722859 0 0 1 1174.206999 722.671035z m578.258824-579.478779l-426.984364 477.155026a25.466567 25.466567 0 0 1-39.953536-30.498883l245.058525-358.81936 68.469993-9.454653a55.812956 55.812956 0 0 0 11.589575-107.813552L1646.939687 59.930305a67.250037 67.250037 0 1 1 105.67863 82.956962z',

            symbolSize: [40, 25], // 散点大小
            cursor: 'pointer', // 鼠标悬浮时在图形元素上时鼠标的样式是什么。同 CSS 的 cursor。
            label: {
              show: true,
              position: 'inside',
              formatter: (params) => {
                return this.shovelproduceData.shovelNameList[params.dataIndex]
              }
            },

            tooltip: {
              backgroundColor: 'rgba(255,255,255,0.7)',
              formatter: (params) => { // 使用箭头函数指向this!!!!!!
                // prettier-ignore
                const shovelproduceData = this.shovelproduceData
                return '<div style="border-bottom: 1px solid rgba(255,255,255,.3); font-size: 18px;padding-bottom: 7px;margin-bottom: 7px">' + '  铲车' +
                shovelproduceData.shovelNameList[params.dataIndex] + '<br>' +
                '</div>' +
                '司机' + '：' + this.shovelproduceData.driverNameList[params.dataIndex] + '<br>' +
                '当前位置' + ':' + '<br>' + params.data + '<br>' +
                '状态' + '：' + this.shovelproduceData.shovelStateList[params.dataIndex] + '<br>'
              }
            }
          },
          {
            name: 'driverwithdemand',
            type: 'effectScatter',
            coordinateSystem: 'geo', // 使用地理坐标系
            data: this.truckwithdemandData.truckLocationList,
            symbol: 'pin',

            symbolSize: 50, // 散点大小
            cursor: 'pointer', // 鼠标悬浮时在图形元素上时鼠标的样式是什么。同 CSS 的 cursor。
            label: {
              show: true,
              position: 'inside',
              formatter: (params) => {
                return this.driverdemand[params.dataIndex][1]
              }
            },
            tooltip: {
              show: false
            }
          }

        ]
      }
      // 爆堆上色
      this.allendpoints.forEach((item, index) => {
        option.geo.regions.push({
          name: item,
          label: { show: true },
          itemStyle: {
            areaColor: colorList[index],
            // borderColor: 'rgb(26,250,41)',
            borderWidth: 1
          }
        })
      })
      myChart.setOption(option)
      if (option && typeof option === 'object') {
        myChart.setOption(option)
      }
      myChart.on('click', function(params) {
        console.log(params)
        if (params.componentSubType === 'effectScatter') {
          const e = params.event.event
          var tip = document.getElementById('tip')
          var btns = [...document.getElementsByClassName('btn')]
          console.log('tip', tip)
          // 自定义设置弹出框的位置
          tip.style.left = e.offsetX - 220 + 'px'
          tip.style.top = e.offsetY - 30 + 'px'
          tip.style.display = 'block'
          const _this = this
          // 为提示框中 Yes/No 按钮绑定点击事件
          btns.forEach((btn) => {
            btn.onclick = (e) => {
            // console.log(e);
              const str = e.target.innerHTML
              tip.style.display = 'none'
              if (str === '确定') {
                console.log('_this.delData')
                console.log(_this.delData)
                _this.delData.push(params.value)
                _this.deldemandpoint()
                // 更新散点图
                _this.setOptions()
              }
            }
          })
        }
      })

      window.addEventListener('resize', myChart.resize)
    },
    getAngles(newValue, oldValue) {
      this.angles = []
      for (let i = 0; i < newValue.truckLocationList.length; i++) {
        const truckPoints = {
          firstpoint: {
            lng: oldValue.truckLocationList[i][0],
            lat: oldValue.truckLocationList[i][1]
          },
          secondpoint: {
            lng: newValue.truckLocationList[i][0],
            lat: newValue.truckLocationList[i][1]
          }
        }
        this.angles.push(this.calculateAngle(truckPoints))
      }
    },
    calculateAngle(points) {
      var position1 = {
        lng: points.firstpoint.lng,
        lat: points.firstpoint.lat
      }
      var position2 = {
        lng: points.secondpoint.lng,
        lat: points.secondpoint.lat
      }
      const valLng = position2.lng - position1.lng
      const valLat = position2.lat - position1.lat

      // 返回一个绝对值
      const absoluteLng = Math.abs(valLng)
      const absoluteLat = Math.abs(valLat)

      // 取得三角形的斜边
      const hypotenuse = Math.hypot(absoluteLng, absoluteLat)
      // 计算弧度
      const radina = Math.acos(absoluteLng / hypotenuse)

      // 计算角度
      let angle = Math.floor(radina * 180 / Math.PI)

      // console.log('两坐标点计算出的角度为：', angle)

      // 计算出标记点真正旋转的角度
      if (valLng > 0) {
        if (valLat > 0) {
          // 第一象限
          angle = angle - 90
        } else {
          // 第四象限
          angle = -angle - 90
        }
      } else {
        if (valLat > 0) {
          // 第二象限
          angle = 90 - angle
        } else {
          // 第三象限
          angle = angle + 90
        }
      }
      // console.log('坐标点真正旋转的角度：', angle)
      return angle
    },
    deldemandpoint() {
      if (this.delData.length > 0) {
        for (let i = 0; i < this.delData.length; i++) {
          for (let j = 0; j < this.truckwithdemandData.truckIdList.length; j++) {
            if (this.delData[i][0] === this.truckwithdemandData.truckIdList[j]) {
              this.truckwithdemandData.truckIdList.splice(j, 1)
              this.truckwithdemandData.truckproduceIndexList.splice(j, 1)
              this.truckwithdemandData.truckLocationList.splice(j, 1)
            }
          }
        }
      }
    }
  }
}

</script>

<style>
/* 提示工具 */
#tip {
    display: none;
    width: 200px;
    height: 45px;
    background-color: gray;
    color: #000;
    border-radius: 6px;
    padding: 5px 0;
    text-align: center;
    /* 因为弹出框要随鼠标移动，所以这里使用绝对定位 */
    position: absolute;
    z-index: 1;
}
/* 为了好看，可以添加一个箭头，也可以选择不加，我这里选择在右侧添加箭头 */
#tip::after {
    content: "";
    position: absolute;

    border-width: 5px;
    border-style: solid;
    /* 1. 在工具提示的右侧添加箭头 */
    top: 50%;
    left: 100%;
    margin-top: -5px;
    border-color: transparent transparent transparent gray;

    /* 2. 在工具提示的左侧添加箭头 */
    /*
    top: 50%;
    right: 100%;
    margin-top: -5px;
    border-color: transparent gray transparent transparent;
    */

    /* 3. 在工具提示的下方添加箭头 */
    /*
    top: 100%;
    left: 50%;
    margin-left: -5px;
    border-color: gray transparent transparent transparent;
    */

    /* 4. 在工具提示的上方添加箭头 */
    /*
    bottom: 100%;
    left: 50%;
    margin-left: -5px;
    border-color: transparent transparent gray transparent; 
    */
}
#tip div {
    text-align: right;
    margin: 0 15px;
}
#tip div button {
    width: 40px;
    height: 22px;
}
</style>
