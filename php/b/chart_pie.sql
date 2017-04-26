--
-- 数据库: `demo`
--

-- --------------------------------------------------------

--
-- 表的结构 `chart_pie`
--

CREATE TABLE IF NOT EXISTS `chart_pie` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(30) NOT NULL,
  `pv` int(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- 转存表中的数据 `chart_pie`
--

INSERT INTO `chart_pie` (`id`, `title`, `pv`) VALUES
(1, '百度', 1239),
(2, 'google', 998),
(3, '搜搜', 342),
(4, '必应', 421),
(5, '搜狗', 259),
(6, '其他', 83);
