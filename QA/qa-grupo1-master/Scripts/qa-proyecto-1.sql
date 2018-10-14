-- phpMyAdmin SQL Dump
-- version 4.8.0.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 18-09-2018 a las 07:00:50
-- Versión del servidor: 10.1.32-MariaDB
-- Versión de PHP: 7.2.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `qa-proyecto-1`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categories`
--

CREATE TABLE `categories` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `Available` bit(1) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `categories`
--

INSERT INTO `categories` (`id`, `name`, `Description`, `Available`, `created_at`, `updated_at`) VALUES
(2, 'Women', 'Las womens', b'1', '2018-09-16 05:09:07', '2018-09-16 05:09:07'),
(3, 'Men', 'Los mens', b'1', '2018-09-16 05:11:46', '2018-09-16 05:11:46'),
(4, 'Chamacos', 'Chamacos', b'1', '2018-09-16 06:14:36', '2018-09-16 06:14:36'),
(5, 'Pollich PLC', 'Et inventore et magnam voluptatem dolorum qui nihil. Nobis et animi fugit assumenda doloribus ad aut voluptas.', b'0', '2018-09-17 03:34:38', '2018-09-17 03:34:38'),
(6, 'Grady-Roob', 'Laboriosam qui ratione inventore similique atque. Qui odio voluptatem et in est qui enim. Mollitia et natus quis asperiores in. Corrupti ut aliquam qui.', b'0', '2018-09-17 03:34:38', '2018-09-17 03:34:38'),
(7, 'Keeling, Altenwerth and Kihn', 'Sed eos qui illo repellendus dicta quo. At eaque saepe ut magni sed eius ut. Voluptatum quis soluta et quibusdam.', b'1', '2018-09-17 03:34:38', '2018-09-17 03:34:38'),
(8, 'Graham-Strosin', 'Quae recusandae reprehenderit tempora beatae omnis id. Asperiores quia sequi quo et dolorum sint exercitationem. Quasi impedit accusamus sint reiciendis dolorem.', b'1', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(9, 'Mertz, Schaefer and Jones', 'Dolorem rerum qui unde. Magnam ea nihil repudiandae voluptas provident. Enim nobis eum et aut commodi eaque. Fugit consectetur minima ducimus. Ducimus cumque in ab aliquid et. Ut harum sunt minima.', b'0', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(10, 'Tillman, Spinka and Volkman', 'Quo ut dolor aut provident reprehenderit fuga. Ratione quas voluptates quia quis ad ut libero. Ex ex impedit rerum et quisquam magni est. Quasi amet tenetur aspernatur enim.', b'1', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(11, 'Feil, Ryan and Pfeffer', 'Tempora consequatur et expedita quas sit ut nam. Quae ut amet illum praesentium. Cumque commodi omnis libero.', b'0', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(12, 'Fritsch-Osinski', 'Voluptatum iste sit voluptatem cum. Officia mollitia quo sed omnis voluptatem debitis hic eos. Explicabo et iure aliquid voluptas. Autem accusamus ipsa distinctio nobis voluptatem ullam voluptatem.', b'1', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(13, 'Gislason Inc', 'Quis voluptate excepturi quia debitis delectus. Aut doloremque odio eos ipsa corrupti. Placeat voluptatem quia ullam inventore ducimus sunt.', b'1', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(14, 'Predovic Group', 'Error quis sunt modi earum ratione sint. Aut harum accusantium qui quibusdam et. Mollitia dolor nulla laboriosam minima velit laboriosam voluptatibus.', b'1', '2018-09-17 03:34:39', '2018-09-17 03:34:39'),
(15, 'Lakin, Bartoletti and Bruen', 'Deleniti qui fugiat ea repellat dolores est. Et quo facere sint est. Qui voluptatibus quis voluptatem. Explicabo delectus aut et dolor aut ut odit. Hic aliquid voluptas esse earum aperiam quidem.', b'0', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(16, 'Howe, Medhurst and Harris', 'Recusandae vero quia quo. Dolore consequuntur hic distinctio placeat voluptas et. Id consequuntur consequatur aut dolores minima suscipit molestias.', b'0', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(17, 'Reichel, Walsh and Greenfelder', 'Fugiat impedit ducimus eius in velit dolorum. Et eum quos illum vel alias asperiores eligendi ratione. Ducimus voluptas vero voluptas et esse ratione.', b'1', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(18, 'Cronin and Sons', 'Molestias velit sint iusto necessitatibus non. Ut voluptatem odio dignissimos. Et deleniti architecto sint laborum corrupti quis. Amet dolore nemo et temporibus at.', b'1', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(19, 'Weber PLC', 'Omnis dolor sunt et consequuntur quas optio. Laudantium aut ipsa est assumenda harum. Totam ducimus placeat illum nam. Pariatur qui enim quo quae.', b'0', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(20, 'Shanahan PLC', 'Et qui eligendi autem non ut. Est maxime sit eaque excepturi. Molestiae omnis dolores architecto autem ex tempora rerum amet. Et quas fuga dolor sunt.', b'1', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(21, 'Gottlieb-Fadel', 'Repellat vel tempore ut pariatur. Id mollitia inventore fugiat consequatur veritatis. Et qui consequuntur vero ducimus quas qui. Unde doloremque eaque accusamus ex qui sit aut voluptas.', b'1', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(22, 'Lemke, Herman and Kling', 'Saepe voluptas sapiente accusantium et aperiam. Numquam magnam illum sunt veniam ea. Beatae quo quia similique harum et.', b'1', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(23, 'Lynch, Hirthe and Harber', 'Consequatur consequatur distinctio id aut in. Molestiae itaque rerum illum ipsum. Nihil neque aut minus earum recusandae. Esse natus rerum praesentium in inventore commodi quo.', b'0', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(24, 'Beatty, Walsh and Koch', 'Enim molestiae quos doloribus exercitationem provident accusamus. Impedit sunt amet magnam quo excepturi recusandae cupiditate. Laborum sed vero blanditiis exercitationem possimus amet.', b'0', '2018-09-17 03:34:56', '2018-09-17 03:34:56'),
(25, 'Douglas-Lynch', 'Incidunt cumque voluptate veritatis rerum minus. Sit est nulla qui. Et cum quasi deserunt recusandae maiores soluta. Iste debitis illum molestiae.', b'0', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(26, 'O\'Connell Ltd', 'Dolor quia quasi maxime voluptas occaecati. Voluptatem qui consequatur corrupti in. Deleniti iste ut est mollitia. Nobis dignissimos voluptates eos culpa quia beatae ipsum.', b'0', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(27, 'Pfeffer-O\'Kon', 'Deleniti placeat voluptatem excepturi eaque. Aperiam nemo sit consequuntur ut error sequi.', b'1', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(28, 'Hodkiewicz-Altenwerth', 'Qui fugit labore quisquam non quia. Quia facilis eaque est et neque illo. Magnam sed similique eius id.', b'1', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(29, 'Crist Group', 'Esse a eos sequi asperiores quia. Placeat consequuntur quasi tempore. Praesentium voluptas sint soluta. Et dolore perferendis nostrum est reiciendis eligendi doloribus dignissimos.', b'0', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(30, 'Abshire-Schultz', 'Aut accusantium reprehenderit et aut in laborum. Expedita fugit quam exercitationem facere quos sit ad ea.', b'1', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(31, 'Hodkiewicz Inc', 'Aut aut labore incidunt sunt tempora tempora non illo. Maiores impedit alias ipsam nisi. Et molestiae qui sed eum eligendi et. Inventore soluta dolorem culpa quia maxime.', b'1', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(32, 'Weber-Raynor', 'Accusantium fuga quis blanditiis consequatur dolorum enim. Iure itaque hic sint reiciendis nisi. Voluptatem minima magni distinctio non sunt.', b'0', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(33, 'Orn, Bruen and Reinger', 'Dolores voluptatem rerum cum voluptatem ducimus qui. Aut ipsam quam sequi. Odio in aut quis eveniet a eaque voluptatem molestias. Nesciunt iure qui inventore et id rerum voluptas reiciendis.', b'0', '2018-09-17 03:35:11', '2018-09-17 03:35:11'),
(34, 'Roberts LLC', 'Inventore ducimus dolorem qui accusamus expedita nisi. Quis adipisci vitae distinctio accusamus et. Qui exercitationem voluptatem porro itaque ea reiciendis.', b'1', '2018-09-17 03:35:11', '2018-09-17 03:35:11');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `data_rows`
--

CREATE TABLE `data_rows` (
  `id` int(10) UNSIGNED NOT NULL,
  `data_type_id` int(10) UNSIGNED NOT NULL,
  `field` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `type` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `display_name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `required` tinyint(1) NOT NULL DEFAULT '0',
  `browse` tinyint(1) NOT NULL DEFAULT '1',
  `read` tinyint(1) NOT NULL DEFAULT '1',
  `edit` tinyint(1) NOT NULL DEFAULT '1',
  `add` tinyint(1) NOT NULL DEFAULT '1',
  `delete` tinyint(1) NOT NULL DEFAULT '1',
  `details` text COLLATE utf8mb4_unicode_ci,
  `order` int(11) NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `data_rows`
--

INSERT INTO `data_rows` (`id`, `data_type_id`, `field`, `type`, `display_name`, `required`, `browse`, `read`, `edit`, `add`, `delete`, `details`, `order`) VALUES
(1, 1, 'id', 'number', 'ID', 1, 0, 0, 0, 0, 0, '', 1),
(2, 1, 'name', 'text', 'Name', 1, 1, 1, 1, 1, 1, '', 2),
(3, 1, 'email', 'text', 'Email', 1, 1, 1, 1, 1, 1, '', 3),
(4, 1, 'password', 'password', 'Password', 1, 0, 0, 1, 1, 0, '', 4),
(5, 1, 'remember_token', 'text', 'Remember Token', 0, 0, 0, 0, 0, 0, '', 5),
(6, 1, 'created_at', 'timestamp', 'Created At', 0, 1, 1, 0, 0, 0, '', 6),
(7, 1, 'updated_at', 'timestamp', 'Updated At', 0, 0, 0, 0, 0, 0, '', 7),
(8, 1, 'avatar', 'image', 'Avatar', 0, 1, 1, 1, 1, 1, '', 8),
(9, 1, 'user_belongsto_role_relationship', 'relationship', 'Role', 0, 1, 1, 1, 1, 0, '{\"model\":\"TCG\\\\Voyager\\\\Models\\\\Role\",\"table\":\"roles\",\"type\":\"belongsTo\",\"column\":\"role_id\",\"key\":\"id\",\"label\":\"display_name\",\"pivot_table\":\"roles\",\"pivot\":\"0\"}', 10),
(10, 1, 'user_belongstomany_role_relationship', 'relationship', 'Roles', 0, 1, 1, 1, 1, 0, '{\"model\":\"TCG\\\\Voyager\\\\Models\\\\Role\",\"table\":\"roles\",\"type\":\"belongsToMany\",\"column\":\"id\",\"key\":\"id\",\"label\":\"display_name\",\"pivot_table\":\"user_roles\",\"pivot\":\"1\",\"taggable\":\"0\"}', 11),
(11, 1, 'locale', 'text', 'Locale', 0, 1, 1, 1, 1, 0, '', 12),
(12, 1, 'settings', 'hidden', 'Settings', 0, 0, 0, 0, 0, 0, '', 12),
(13, 2, 'id', 'number', 'ID', 1, 0, 0, 0, 0, 0, '', 1),
(14, 2, 'name', 'text', 'Name', 1, 1, 1, 1, 1, 1, '', 2),
(15, 2, 'created_at', 'timestamp', 'Created At', 0, 0, 0, 0, 0, 0, '', 3),
(16, 2, 'updated_at', 'timestamp', 'Updated At', 0, 0, 0, 0, 0, 0, '', 4),
(17, 3, 'id', 'number', 'ID', 1, 0, 0, 0, 0, 0, '', 1),
(18, 3, 'name', 'text', 'Name', 1, 1, 1, 1, 1, 1, '', 2),
(19, 3, 'created_at', 'timestamp', 'Created At', 0, 0, 0, 0, 0, 0, '', 3),
(20, 3, 'updated_at', 'timestamp', 'Updated At', 0, 0, 0, 0, 0, 0, '', 4),
(21, 3, 'display_name', 'text', 'Display Name', 1, 1, 1, 1, 1, 1, '', 5),
(22, 1, 'role_id', 'text', 'Role', 1, 1, 1, 1, 1, 1, '', 9),
(27, 5, 'id', 'text', 'Id', 1, 0, 0, 0, 0, 0, NULL, 1),
(28, 5, 'Name', 'text', 'Name', 1, 1, 1, 1, 1, 1, NULL, 2),
(29, 5, 'Description', 'text', 'Description', 1, 1, 1, 1, 1, 1, NULL, 3),
(31, 5, 'Price', 'number', 'Price', 1, 1, 1, 1, 1, 1, NULL, 5),
(32, 5, 'Inventory', 'number', 'Inventory', 1, 1, 1, 1, 1, 1, NULL, 6),
(33, 5, 'created_at', 'timestamp', 'Created At', 0, 1, 1, 1, 0, 1, NULL, 7),
(34, 5, 'updated_at', 'timestamp', 'Updated At', 0, 0, 0, 0, 0, 0, NULL, 8),
(35, 5, 'Photo', 'image', 'Photo', 0, 1, 1, 1, 1, 1, NULL, 9),
(36, 5, 'idCategory', 'text', 'IdCategory', 1, 1, 1, 1, 1, 1, NULL, 10),
(37, 5, 'product_belongsto_category_relationship', 'relationship', 'categories', 0, 1, 1, 1, 1, 1, '{\"model\":\"QA_Store\\\\Category\",\"table\":\"categories\",\"type\":\"belongsTo\",\"column\":\"idCategory\",\"key\":\"id\",\"label\":\"name\",\"pivot_table\":\"categories\",\"pivot\":\"0\",\"taggable\":\"0\"}', 11),
(38, 5, 'Available', 'checkbox', 'Available', 1, 1, 1, 1, 1, 1, NULL, 4),
(40, 6, 'id', 'text', 'Id', 1, 0, 0, 0, 0, 0, NULL, 1),
(41, 6, 'name', 'text', 'Name', 1, 1, 1, 1, 1, 1, NULL, 2),
(42, 6, 'Description', 'text', 'Description', 1, 1, 1, 1, 1, 1, NULL, 3),
(43, 6, 'Available', 'text', 'Available', 1, 1, 1, 1, 1, 1, NULL, 4),
(44, 6, 'created_at', 'timestamp', 'Created At', 0, 1, 1, 1, 0, 1, NULL, 5),
(45, 6, 'updated_at', 'timestamp', 'Updated At', 0, 0, 0, 0, 0, 0, NULL, 6),
(46, 6, 'category_hasmany_product_relationship', 'relationship', 'products', 0, 1, 1, 1, 1, 1, '{\"model\":\"QA_Store\\\\Product\",\"table\":\"products\",\"type\":\"hasMany\",\"column\":\"idcategory\",\"key\":\"id\",\"label\":\"id\",\"pivot_table\":\"categories\",\"pivot\":\"0\",\"taggable\":null}', 7);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `data_types`
--

CREATE TABLE `data_types` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `slug` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `display_name_singular` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `display_name_plural` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `icon` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `model_name` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `policy_name` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `controller` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `description` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `generate_permissions` tinyint(1) NOT NULL DEFAULT '0',
  `server_side` tinyint(4) NOT NULL DEFAULT '0',
  `details` text COLLATE utf8mb4_unicode_ci,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `data_types`
--

INSERT INTO `data_types` (`id`, `name`, `slug`, `display_name_singular`, `display_name_plural`, `icon`, `model_name`, `policy_name`, `controller`, `description`, `generate_permissions`, `server_side`, `details`, `created_at`, `updated_at`) VALUES
(1, 'users', 'users', 'User', 'Users', 'voyager-person', 'TCG\\Voyager\\Models\\User', 'TCG\\Voyager\\Policies\\UserPolicy', '', '', 1, 0, NULL, '2018-09-16 02:42:44', '2018-09-16 02:42:44'),
(2, 'menus', 'menus', 'Menu', 'Menus', 'voyager-list', 'TCG\\Voyager\\Models\\Menu', NULL, '', '', 1, 0, NULL, '2018-09-16 02:42:44', '2018-09-16 02:42:44'),
(3, 'roles', 'roles', 'Role', 'Roles', 'voyager-lock', 'TCG\\Voyager\\Models\\Role', NULL, '', '', 1, 0, NULL, '2018-09-16 02:42:44', '2018-09-16 02:42:44'),
(5, 'products', 'products', 'Product', 'Products', NULL, 'QA_Store\\Product', NULL, NULL, NULL, 1, 0, '{\"order_column\":null,\"order_display_column\":null}', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(6, 'categories', 'categories', 'Category', 'Categories', NULL, 'QA_Store\\Category', NULL, NULL, NULL, 1, 0, '{\"order_column\":null,\"order_display_column\":null}', '2018-09-18 00:57:53', '2018-09-18 00:57:53');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `menus`
--

CREATE TABLE `menus` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `menus`
--

INSERT INTO `menus` (`id`, `name`, `created_at`, `updated_at`) VALUES
(1, 'admin', '2018-09-16 02:42:57', '2018-09-16 02:42:57');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `menu_items`
--

CREATE TABLE `menu_items` (
  `id` int(10) UNSIGNED NOT NULL,
  `menu_id` int(10) UNSIGNED DEFAULT NULL,
  `title` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `url` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `target` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '_self',
  `icon_class` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `color` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `parent_id` int(11) DEFAULT NULL,
  `order` int(11) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  `route` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `parameters` text COLLATE utf8mb4_unicode_ci
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `menu_items`
--

INSERT INTO `menu_items` (`id`, `menu_id`, `title`, `url`, `target`, `icon_class`, `color`, `parent_id`, `order`, `created_at`, `updated_at`, `route`, `parameters`) VALUES
(1, 1, 'Dashboard', '', '_self', 'voyager-boat', NULL, NULL, 1, '2018-09-16 02:42:57', '2018-09-16 02:42:57', 'voyager.dashboard', NULL),
(2, 1, 'Media', '', '_self', 'voyager-images', NULL, 5, 2, '2018-09-16 02:42:58', '2018-09-18 02:23:11', 'voyager.media.index', NULL),
(3, 1, 'Users', '', '_self', 'voyager-person', NULL, NULL, 2, '2018-09-16 02:42:58', '2018-09-17 21:52:29', 'voyager.users.index', NULL),
(4, 1, 'Roles', '', '_self', 'voyager-lock', NULL, 5, 1, '2018-09-16 02:42:59', '2018-09-18 02:23:11', 'voyager.roles.index', NULL),
(5, 1, 'Tools', '', '_self', 'voyager-tools', NULL, NULL, 5, '2018-09-16 02:42:59', '2018-09-18 02:23:11', NULL, NULL),
(6, 1, 'Menu Builder', '', '_self', 'voyager-list', NULL, 5, 3, '2018-09-16 02:42:59', '2018-09-18 02:23:11', 'voyager.menus.index', NULL),
(7, 1, 'Database', '', '_self', 'voyager-data', NULL, 5, 4, '2018-09-16 02:43:00', '2018-09-18 02:23:11', 'voyager.database.index', NULL),
(8, 1, 'Compass', '', '_self', 'voyager-compass', NULL, 5, 5, '2018-09-16 02:43:00', '2018-09-18 02:23:11', 'voyager.compass.index', NULL),
(9, 1, 'BREAD', '', '_self', 'voyager-bread', NULL, 5, 6, '2018-09-16 02:43:01', '2018-09-18 02:23:11', 'voyager.bread.index', NULL),
(10, 1, 'Settings', '', '_self', 'voyager-settings', NULL, 5, 8, '2018-09-16 02:43:01', '2018-09-18 02:23:11', 'voyager.settings.index', NULL),
(11, 1, 'Hooks', '', '_self', 'voyager-hook', NULL, 5, 7, '2018-09-16 02:43:24', '2018-09-18 02:23:11', 'voyager.hooks', NULL),
(12, 1, 'Categories', '', '_self', 'voyager-categories', '#000000', NULL, 3, '2018-09-16 05:07:45', '2018-09-17 21:52:52', 'voyager.categories.index', 'null'),
(13, 1, 'Products', '', '_self', 'voyager-bag', '#000000', NULL, 4, '2018-09-17 21:55:58', '2018-09-17 23:32:24', 'voyager.products.index', 'null');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `migrations`
--

CREATE TABLE `migrations` (
  `id` int(10) UNSIGNED NOT NULL,
  `migration` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `batch` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `migrations`
--

INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
(1, '2014_10_12_000000_create_users_table', 1),
(2, '2014_10_12_100000_create_password_resets_table', 1),
(3, '2016_01_01_000000_add_voyager_user_fields', 1),
(4, '2016_01_01_000000_create_data_types_table', 1),
(5, '2016_05_19_173453_create_menu_table', 1),
(6, '2016_10_21_190000_create_roles_table', 1),
(7, '2016_10_21_190000_create_settings_table', 1),
(8, '2016_11_30_135954_create_permission_table', 1),
(9, '2016_11_30_141208_create_permission_role_table', 1),
(10, '2016_12_26_201236_data_types__add__server_side', 1),
(11, '2017_01_13_000000_add_route_to_menu_items_table', 1),
(12, '2017_01_14_005015_create_translations_table', 1),
(13, '2017_01_15_000000_make_table_name_nullable_in_permissions_table', 1),
(14, '2017_03_06_000000_add_controller_to_data_types_table', 1),
(15, '2017_04_21_000000_add_order_to_data_rows_table', 1),
(16, '2017_07_05_210000_add_policyname_to_data_types_table', 1),
(17, '2017_08_05_000000_add_group_to_settings_table', 1),
(18, '2017_11_26_013050_add_user_role_relationship', 1),
(19, '2017_11_26_015000_create_user_roles_table', 1),
(20, '2018_03_11_000000_add_user_settings', 1),
(21, '2018_03_14_000000_add_details_to_data_types_table', 1),
(22, '2018_03_16_000000_make_settings_value_nullable', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `password_resets`
--

CREATE TABLE `password_resets` (
  `email` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `token` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `permissions`
--

CREATE TABLE `permissions` (
  `id` int(10) UNSIGNED NOT NULL,
  `key` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `table_name` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `permissions`
--

INSERT INTO `permissions` (`id`, `key`, `table_name`, `created_at`, `updated_at`) VALUES
(1, 'browse_admin', NULL, '2018-09-16 02:43:03', '2018-09-16 02:43:03'),
(2, 'browse_bread', NULL, '2018-09-16 02:43:03', '2018-09-16 02:43:03'),
(3, 'browse_database', NULL, '2018-09-16 02:43:04', '2018-09-16 02:43:04'),
(4, 'browse_media', NULL, '2018-09-16 02:43:04', '2018-09-16 02:43:04'),
(5, 'browse_compass', NULL, '2018-09-16 02:43:04', '2018-09-16 02:43:04'),
(6, 'browse_menus', 'menus', '2018-09-16 02:43:04', '2018-09-16 02:43:04'),
(7, 'read_menus', 'menus', '2018-09-16 02:43:05', '2018-09-16 02:43:05'),
(8, 'edit_menus', 'menus', '2018-09-16 02:43:05', '2018-09-16 02:43:05'),
(9, 'add_menus', 'menus', '2018-09-16 02:43:05', '2018-09-16 02:43:05'),
(10, 'delete_menus', 'menus', '2018-09-16 02:43:05', '2018-09-16 02:43:05'),
(11, 'browse_roles', 'roles', '2018-09-16 02:43:05', '2018-09-16 02:43:05'),
(12, 'read_roles', 'roles', '2018-09-16 02:43:06', '2018-09-16 02:43:06'),
(13, 'edit_roles', 'roles', '2018-09-16 02:43:06', '2018-09-16 02:43:06'),
(14, 'add_roles', 'roles', '2018-09-16 02:43:06', '2018-09-16 02:43:06'),
(15, 'delete_roles', 'roles', '2018-09-16 02:43:07', '2018-09-16 02:43:07'),
(16, 'browse_users', 'users', '2018-09-16 02:43:07', '2018-09-16 02:43:07'),
(17, 'read_users', 'users', '2018-09-16 02:43:08', '2018-09-16 02:43:08'),
(18, 'edit_users', 'users', '2018-09-16 02:43:08', '2018-09-16 02:43:08'),
(19, 'add_users', 'users', '2018-09-16 02:43:09', '2018-09-16 02:43:09'),
(20, 'delete_users', 'users', '2018-09-16 02:43:09', '2018-09-16 02:43:09'),
(21, 'browse_settings', 'settings', '2018-09-16 02:43:09', '2018-09-16 02:43:09'),
(22, 'read_settings', 'settings', '2018-09-16 02:43:10', '2018-09-16 02:43:10'),
(23, 'edit_settings', 'settings', '2018-09-16 02:43:10', '2018-09-16 02:43:10'),
(24, 'add_settings', 'settings', '2018-09-16 02:43:10', '2018-09-16 02:43:10'),
(25, 'delete_settings', 'settings', '2018-09-16 02:43:11', '2018-09-16 02:43:11'),
(26, 'browse_hooks', NULL, '2018-09-16 02:43:24', '2018-09-16 02:43:24'),
(32, 'browse_products', 'products', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(33, 'read_products', 'products', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(34, 'edit_products', 'products', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(35, 'add_products', 'products', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(36, 'delete_products', 'products', '2018-09-17 21:55:58', '2018-09-17 21:55:58'),
(37, 'browse_categories', 'categories', '2018-09-18 00:57:53', '2018-09-18 00:57:53'),
(38, 'read_categories', 'categories', '2018-09-18 00:57:53', '2018-09-18 00:57:53'),
(39, 'edit_categories', 'categories', '2018-09-18 00:57:53', '2018-09-18 00:57:53'),
(40, 'add_categories', 'categories', '2018-09-18 00:57:53', '2018-09-18 00:57:53'),
(41, 'delete_categories', 'categories', '2018-09-18 00:57:53', '2018-09-18 00:57:53');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `permission_role`
--

CREATE TABLE `permission_role` (
  `permission_id` int(10) UNSIGNED NOT NULL,
  `role_id` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `permission_role`
--

INSERT INTO `permission_role` (`permission_id`, `role_id`) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 1),
(8, 1),
(9, 1),
(10, 1),
(11, 1),
(12, 1),
(13, 1),
(14, 1),
(15, 1),
(16, 1),
(17, 1),
(18, 1),
(19, 1),
(20, 1),
(21, 1),
(22, 1),
(23, 1),
(24, 1),
(25, 1),
(26, 1),
(32, 1),
(33, 1),
(34, 1),
(35, 1),
(36, 1),
(37, 1),
(38, 1),
(39, 1),
(40, 1),
(41, 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `products`
--

CREATE TABLE `products` (
  `id` int(10) UNSIGNED NOT NULL,
  `Name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `Description` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `Available` bit(1) NOT NULL,
  `Price` decimal(16,5) NOT NULL,
  `Inventory` int(11) NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  `Photo` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT 'products/default.jpg',
  `idCategory` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `products`
--

INSERT INTO `products` (`id`, `Name`, `Description`, `Available`, `Price`, `Inventory`, `created_at`, `updated_at`, `Photo`, `idCategory`) VALUES
(2, 'Adidas Shirt Fresca', 'Una camisa adidas toda fresca', b'1', '420.00000', 2, '2018-09-17 23:34:00', '2018-09-17 23:35:26', 'products\\September2018\\OiBv7NZj3WsDv2MdNKQe.jpg', 3),
(3, 'Ritchie, Hodkiewicz and Schoen', 'Aut dolorem commodi cum nobis corrupti distinctio ea eos. Magnam occaecati ut optio quibusdam ducimus odio dolore. Aliquam amet eum et aut in nihil molestiae.', b'0', '12.00000', 14, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 11),
(4, 'Ernser PLC', 'Perspiciatis accusamus magni accusantium dolorum. Blanditiis molestiae et error quis minus. Corporis officiis asperiores dolorum itaque eos. Atque et minima temporibus officia temporibus ipsum id ex.', b'0', '39.00000', 8, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 26),
(5, 'Roob-Hackett', 'Eos aliquam sunt voluptate perferendis. Cum vitae autem et et. Ut veniam error quisquam assumenda. Iure eos quasi et.', b'1', '37.00000', 15, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 30),
(6, 'Goyette-Ortiz', 'Similique sed quisquam magni facilis. Sapiente veritatis facilis optio dignissimos vel maiores. Qui odit asperiores quisquam eligendi sapiente voluptatem. Iusto fuga itaque cupiditate sapiente qui.', b'0', '35.00000', 5, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 32),
(7, 'Harvey, Hessel and Rutherford', 'Rerum voluptatibus sit natus et ut eveniet. Facilis ut vel tenetur omnis molestiae sed quo. Sit ducimus non numquam et. Quibusdam alias numquam quisquam.', b'1', '17.00000', 9, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 33),
(8, 'Waters, Prohaska and Beier', 'Id dolor quidem excepturi voluptatem. Voluptatem ad nihil repellendus ipsam enim. Qui molestiae nobis aperiam natus.', b'0', '56.00000', 6, '2018-09-18 01:17:13', '2018-09-18 01:17:13', 'products/default.jpg', 16),
(9, 'Cummerata-Feeney', 'Perspiciatis unde unde eveniet ipsa deserunt dolore. Nemo quo tempore dolorem vel iste animi delectus. Blanditiis blanditiis adipisci tenetur sapiente voluptatem asperiores.', b'0', '37.00000', 9, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 20),
(10, 'Schneider Inc', 'Est iusto occaecati sit eum. Aspernatur delectus cumque deserunt. Veritatis autem dolorem tenetur animi sit. Velit sapiente molestiae et alias.', b'1', '47.00000', 10, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 13),
(11, 'Reichert Group', 'Atque officia ut temporibus accusamus. Ab odio voluptas nisi. Ab nesciunt ipsa et ut. Quas earum in nobis consequatur molestiae nisi.', b'1', '55.00000', 10, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 24),
(12, 'O\'Kon and Sons', 'Possimus architecto dolore deserunt sit commodi esse ratione. Odit quaerat laborum doloremque iste.', b'1', '29.00000', 14, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 18),
(13, 'Pagac, Considine and Cartwright', 'Consectetur eveniet debitis soluta deserunt et vel. Quidem vel praesentium enim exercitationem qui. Omnis aut aliquid amet consectetur. Cumque qui ut quae voluptatum sed excepturi non sint.', b'0', '26.00000', 1, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 20),
(14, 'Osinski, Lueilwitz and Kuhlman', 'Sint error reiciendis commodi ea accusamus ut. Voluptatem dolorum quos illum ut occaecati quis autem. Dicta aliquam libero recusandae voluptatem eum. Ratione culpa et error ad id et sunt.', b'1', '33.00000', 8, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 12),
(15, 'Mraz, Jones and Langworth', 'Ut sed et ut quam id alias culpa animi. Facere aut accusantium vero et tenetur ut. Aperiam dolores ea sequi qui et. Alias magni dolorem laudantium porro iure iusto. Dolor eos debitis ducimus iure.', b'0', '13.00000', 10, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 7),
(16, 'Altenwerth LLC', 'Omnis quia debitis labore facilis et nihil. Rerum quis nulla dolorem dolorum et. Sit beatae numquam hic aliquid ut alias sint. Et praesentium eum reiciendis non ipsam.', b'1', '55.00000', 7, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 8),
(17, 'Rolfson Inc', 'Expedita dolores iusto consequuntur. Minus perferendis consequatur occaecati doloribus. Nihil a molestiae quia debitis.', b'0', '14.00000', 13, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 5),
(18, 'Senger, Baumbach and Kuhlman', 'Sunt consequatur sunt eius perferendis consequatur. Dolorem occaecati temporibus odio itaque hic ipsum. Ipsa eligendi maxime magni placeat sequi culpa non. Ipsa nam praesentium aut voluptatum.', b'1', '25.00000', 4, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 19),
(19, 'Crona, Rolfson and Leffler', 'Inventore ratione praesentium nihil. Autem neque voluptas delectus. Rerum totam est ex consequatur ratione veniam.', b'0', '53.00000', 9, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 17),
(20, 'Parker-Schulist', 'Accusamus qui corporis esse voluptatem. In voluptate quasi in. Tempora enim tempore sint molestiae facilis mollitia.', b'0', '33.00000', 13, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 31),
(21, 'Spinka, Considine and Hudson', 'Inventore reprehenderit est excepturi est quaerat qui voluptates. Qui nemo nostrum ut. Quia omnis doloribus molestiae laborum sit.', b'1', '18.00000', 8, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 6),
(22, 'Reichel-Williamson', 'Nobis voluptate consequatur repellat et sapiente est. Ipsam rerum necessitatibus dolores sed corrupti. Accusamus rem enim veritatis quia in. Ut aliquam assumenda ut iure.', b'0', '47.00000', 9, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 23),
(23, 'Greenholt-Bartell', 'Tenetur amet consectetur aut quod. Non harum accusantium placeat rerum nisi. Ad quia facilis impedit qui natus.', b'0', '32.00000', 4, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 18),
(24, 'Considine, Toy and Koss', 'Doloribus minima corrupti reprehenderit sed qui. Delectus ex nihil error natus dolore quasi modi. Similique eum cupiditate modi aut ut. Fugit et placeat et omnis.', b'0', '43.00000', 5, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 19),
(25, 'Langworth, Heller and Shields', 'Iure id quasi nihil et omnis. Et et alias quis fugit fugiat ipsa dolor ipsum. Iste reiciendis quaerat neque.', b'1', '28.00000', 4, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 5),
(26, 'Klocko-Miller', 'Vitae molestias eveniet voluptatem fugiat voluptatem. Consequatur natus sapiente quia quae odio.', b'0', '17.00000', 11, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 33),
(27, 'McGlynn Inc', 'Laboriosam sapiente quam nihil voluptatum fugiat eum. Qui inventore et et mollitia voluptatem rerum nulla. Eum perferendis omnis illum magni et cum est.', b'0', '54.00000', 12, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 2),
(28, 'Franecki, Klocko and Shanahan', 'Aperiam qui sint totam omnis vitae rem ea corporis. Blanditiis quo assumenda ipsa sint. Soluta magnam facilis eligendi quis minus dolorem qui. Commodi nobis ipsum quaerat id.', b'1', '51.00000', 9, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 13),
(29, 'Smitham PLC', 'Quae ipsa exercitationem alias quam in quam. Aut delectus aspernatur fuga occaecati. Inventore quia rem ut harum labore. Quis cupiditate est laboriosam fuga.', b'0', '42.00000', 14, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 23),
(30, 'Daugherty LLC', 'Porro quasi ipsam sapiente laborum labore earum. Aut dolorum id aut voluptatem sed vel. Nostrum dolor magnam repellat eos expedita praesentium non. Excepturi itaque consequatur illum voluptas totam.', b'1', '38.00000', 10, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 21),
(31, 'Upton Group', 'Recusandae aliquid consectetur excepturi suscipit quae et commodi vel. Sit atque voluptatum sit voluptatem sit enim quasi. Nesciunt debitis reiciendis quia et. Perferendis enim magni quas.', b'0', '25.00000', 8, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 22),
(32, 'Cummings-Koch', 'Soluta est eum quod. Necessitatibus et exercitationem sit velit quas quod. Natus excepturi aut impedit sit. Nihil et deserunt in libero.', b'0', '55.00000', 9, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 18),
(33, 'Bechtelar and Sons', 'Repudiandae quia praesentium quis ducimus dignissimos numquam. Sapiente temporibus enim praesentium soluta beatae iure. Accusantium dolore nesciunt magnam vero earum. Consequatur id beatae incidunt.', b'0', '16.00000', 10, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 11),
(34, 'Kautzer-Grady', 'In velit qui beatae sed. Totam nisi in eum rerum officiis. Aut adipisci quia nisi sed aut neque.', b'1', '16.00000', 15, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 32),
(35, 'Quitzon LLC', 'Aliquid tempore qui adipisci voluptatem. Aut incidunt quasi pariatur vel id autem est eaque. Et hic vero incidunt et omnis nihil voluptatem.', b'1', '43.00000', 12, '2018-09-18 01:17:14', '2018-09-18 01:17:14', 'products/default.jpg', 13),
(36, 'Zieme-West', 'Sunt dicta incidunt nihil et blanditiis et sunt eveniet. Voluptatem numquam ipsa vel numquam deserunt. Ratione vel dignissimos quidem sequi quibusdam doloremque impedit.', b'0', '52.00000', 7, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 23),
(37, 'Bogisich-Boyer', 'Sunt sit ex omnis est beatae dolore. Ex molestiae porro accusamus modi iusto facere ratione. Quia quia rerum modi eligendi. Et nemo repellat quae fugit dignissimos.', b'0', '51.00000', 3, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 2),
(38, 'Jacobson, Weissnat and Hettinger', 'Ut sapiente totam voluptate non exercitationem quo deleniti. Nesciunt nisi voluptatem consequatur et id suscipit distinctio expedita.', b'0', '36.00000', 11, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 27),
(39, 'Jakubowski-Rowe', 'Temporibus quos id laborum dolorum labore molestiae dolorum. Quisquam ut modi consectetur dolores. Et commodi expedita assumenda sunt nihil dolore. Nostrum asperiores mollitia aut corrupti.', b'1', '38.00000', 14, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 5),
(40, 'Olson Inc', 'Aliquam minus harum ab est sit tenetur. Itaque corrupti ducimus placeat pariatur quod. Dolore mollitia itaque dolore nostrum. Enim voluptatibus voluptatum est aut sed totam quia.', b'0', '60.00000', 15, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 13),
(41, 'Gibson-Cole', 'Vero soluta quasi est accusamus accusamus odit necessitatibus. Commodi atque voluptatem odio quibusdam eum. Ea quia ea dolores odit.', b'1', '19.00000', 15, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 25),
(42, 'Lowe, Lesch and Armstrong', 'Omnis dolor accusantium officiis est enim. Est qui id ex accusamus tempora. Architecto expedita quo culpa omnis vitae dolorem quam. Eaque tenetur dolorem soluta quis ipsam pariatur.', b'1', '48.00000', 6, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 27),
(43, 'Gleichner, Russel and Goldner', 'Fugit voluptatem architecto facilis qui in rerum dolorem. Accusamus dolorem quidem non et a molestias. Quis esse perspiciatis iure. Numquam quo non eos nihil quod.', b'1', '29.00000', 1, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 30),
(44, 'Swaniawski-Huels', 'Qui voluptatem ut consequuntur aut. Modi quo ducimus praesentium expedita doloribus et ex. Accusamus voluptates explicabo et.', b'1', '25.00000', 15, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 9),
(45, 'Gibson, Gerhold and Corkery', 'Et sed doloribus sint. Voluptas consequatur dignissimos aut blanditiis. Labore voluptatem aliquam nam maxime.', b'0', '49.00000', 8, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 17),
(46, 'Grimes, Pouros and Altenwerth', 'Ut sit voluptate laudantium et perspiciatis. Qui sint voluptatem corporis eaque incidunt culpa. Et iusto et omnis.', b'1', '59.00000', 1, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 6),
(47, 'Jast, Hahn and Hickle', 'Magni aut voluptatibus et. Ea enim officiis qui aut quia accusamus. Non vero beatae ex ratione.', b'0', '26.00000', 14, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 30),
(48, 'Reilly and Sons', 'Mollitia maxime consequatur voluptas neque et. Asperiores debitis molestiae sapiente omnis cum fugit. Nam nostrum illum asperiores eum. Voluptatem doloribus non iste error.', b'1', '24.00000', 7, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 12),
(49, 'Oberbrunner-Doyle', 'Ipsum qui officiis modi consequatur officia nemo. Nulla sint voluptate fugit quod magni occaecati numquam. Illo est repellendus adipisci accusamus tempore. Eaque ut et sed magnam est.', b'1', '13.00000', 15, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 24),
(50, 'Stamm-Spencer', 'Autem aspernatur quasi neque ducimus laborum voluptatem est. Sit in ut dolores error iure. Minima est ullam doloremque iure.', b'0', '25.00000', 7, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 25),
(51, 'Friesen and Sons', 'Hic voluptates et perferendis nobis sit qui. Minima facere ut sed. Sit consequatur illo voluptas illo.', b'1', '30.00000', 9, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 21),
(52, 'Prosacco LLC', 'Sed et animi maiores est dolorem placeat non. Voluptatem molestias alias cumque placeat. Eos nam ut voluptas dolores aut optio qui quaerat. Ut perferendis fugit qui officia voluptatibus magnam.', b'1', '38.00000', 1, '2018-09-18 01:17:00', '2018-09-18 01:30:28', 'products/default.jpg', 4),
(53, 'Mitchell, Tremblay and Prohaska', 'Esse et recusandae reprehenderit corporis. Officia possimus id esse sequi ipsum. Et et quisquam voluptatem itaque eum ut laboriosam. Ea aut quod nostrum natus eaque doloremque.', b'1', '12.00000', 4, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 5),
(54, 'Will-Mayer', 'Voluptas qui debitis sit id voluptatem soluta. Quibusdam enim dolorum eum impedit ipsam at nesciunt.', b'0', '47.00000', 5, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 10),
(55, 'Hegmann-Gulgowski', 'Eius quia minima eos a. Et est praesentium enim est nisi. At non quam esse. Commodi provident aut labore in non excepturi amet.', b'1', '46.00000', 10, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 32),
(56, 'Reynolds, Heaney and Haley', 'Voluptas et est adipisci. Cumque accusamus consequatur est eligendi. Aut vero quibusdam eum est. Perspiciatis et nisi esse in vel est. Eius debitis omnis velit quia.', b'1', '60.00000', 14, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 7),
(57, 'Crist LLC', 'Ut delectus illo dolorum adipisci quisquam. Consequatur et ipsa rem dolores. Eos et accusamus quisquam maxime qui enim perspiciatis temporibus.', b'1', '28.00000', 3, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 28),
(58, 'Kutch, Mayer and Huels', 'Odit ex recusandae sed eius id harum doloribus ut. Sunt vel ab unde accusamus temporibus non. Natus qui aut totam voluptatem tempore illo consequuntur.', b'0', '28.00000', 12, '2018-09-18 01:17:15', '2018-09-18 01:17:15', 'products/default.jpg', 17),
(59, 'Schuster-Yost', 'Aut quod sed quaerat ducimus nostrum consequatur blanditiis. Aliquid autem sit esse dolores. Accusamus rerum accusantium illo.', b'1', '29.00000', 11, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 26),
(60, 'Kunze-Keeling', 'Velit laborum quia quisquam sapiente nihil. Ut quo et suscipit non est. Neque sapiente esse dolores consectetur. Quam et enim aliquam tempora voluptatem et ipsa.', b'0', '13.00000', 11, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 31),
(61, 'Simonis, Cremin and Balistreri', 'Aut vel dolorum voluptas ducimus ut consectetur autem. Ut aut reprehenderit vitae earum. Beatae omnis omnis vero voluptates id. Eligendi voluptates deleniti saepe error occaecati.', b'0', '34.00000', 4, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 20),
(62, 'Wolf-Hartmann', 'Velit aspernatur quaerat officia. Est quidem sint accusantium dignissimos est. Eos enim ducimus totam et. Ut quo nisi minus.', b'0', '25.00000', 3, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 19),
(63, 'Schmeler Ltd', 'Est aliquam cumque porro et ipsam aliquid provident officia. Et esse mollitia dolorem quis delectus et. Error odio et commodi delectus aut.', b'0', '34.00000', 9, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 6),
(64, 'Feest-Conroy', 'Dolorem eos debitis aut inventore autem saepe veniam dolorem. Iste doloribus nulla ut blanditiis aut. Consequatur repellat et qui commodi dolore id.', b'1', '38.00000', 12, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 2),
(65, 'Osinski, Zulauf and Dicki', 'Odio aliquam optio et facere soluta similique. Voluptatum fugit consequatur dolorem. Culpa unde et facilis quam eaque repellat.', b'0', '58.00000', 14, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 28),
(66, 'Ortiz, Cremin and Aufderhar', 'Molestiae occaecati libero a quia minus eius. Fugiat voluptatem perspiciatis non nisi. Porro accusamus omnis cumque rerum.', b'0', '42.00000', 15, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 31),
(67, 'Lesch, Cormier and Stoltenberg', 'Ut molestiae harum dolorem dolorem maxime aut. Quo qui aut magni aut. Omnis possimus quo eos nihil optio laudantium. Facilis sequi error earum et. Cum voluptatum reprehenderit nam vel facere.', b'0', '15.00000', 6, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 8),
(68, 'Boyle and Sons', 'Aut eveniet eos dignissimos minima rerum saepe. Accusamus cumque quia facere dolorem aut sunt.', b'1', '42.00000', 14, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 2),
(69, 'Abbott-Jacobi', 'Minus fugiat velit sequi nihil debitis consequatur sed in. In eligendi rerum consequatur aut doloribus odit optio. Nulla corporis cumque ea est odit numquam repudiandae. Debitis et vel magni.', b'0', '46.00000', 2, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 22),
(70, 'O\'Keefe, Kemmer and Moen', 'Dolor voluptas sit tempora. Incidunt tempora eos ut possimus itaque. Tempore sit nihil natus. Cupiditate qui repellat nostrum sit optio eius. Et et ea ad repellat odio eos ducimus accusantium.', b'0', '29.00000', 2, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 34),
(71, 'Dickinson, Bartell and Dietrich', 'Vitae id quis rerum est provident et. Quaerat porro sunt consectetur nulla. Rerum error consequatur aspernatur sequi voluptas.', b'1', '46.00000', 8, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 7),
(72, 'Bergnaum Ltd', 'Quia aperiam quo illum dolores porro. Ipsam at et numquam tenetur eos modi aut. Eligendi cum nihil atque. Et quisquam nisi occaecati iusto sequi ipsum dolorem.', b'1', '56.00000', 12, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 14),
(73, 'Cruickshank and Sons', 'Aut est ut est mollitia totam sed quo et. Omnis dolorum debitis natus asperiores. Et sunt distinctio ea temporibus consequatur maxime assumenda.', b'1', '54.00000', 12, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 13),
(74, 'Bradtke-Ward', 'Qui quos exercitationem aut expedita qui amet quo. Voluptatum et consectetur qui impedit velit qui reprehenderit. Est et corporis qui dolorem. Occaecati neque quaerat quasi labore.', b'0', '55.00000', 11, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 7),
(75, 'McGlynn, Kshlerin and Hand', 'Dolores quos facere ad tempora dolor id praesentium. Praesentium cumque aperiam iure odit. Et repellendus omnis perferendis nihil earum quae qui.', b'0', '17.00000', 10, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 28),
(76, 'Ritchie LLC', 'Ex sunt eaque inventore ipsam molestias quis debitis. Reiciendis accusantium molestiae voluptatibus officia. Magnam vel velit voluptates excepturi.', b'0', '57.00000', 4, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 7),
(77, 'Konopelski, Boyle and Tromp', 'Voluptates reiciendis aut laboriosam. Consequuntur ipsam a fuga ut expedita. Rerum magni perspiciatis molestiae ut quia recusandae occaecati.', b'1', '33.00000', 14, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 2),
(78, 'Ratke-Considine', 'Id ea porro fugiat. Minima culpa alias unde. Ut nam odit inventore hic.', b'0', '23.00000', 10, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 5),
(79, 'Morissette PLC', 'Doloremque asperiores doloribus ipsam rerum est aut. Quo voluptatem voluptatibus nam molestias expedita. Delectus iusto mollitia aut aliquam.', b'0', '27.00000', 12, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 19),
(80, 'Schumm, Crist and Jakubowski', 'Quaerat consectetur nobis expedita. Provident harum illum facere quis magni. Voluptatem vel et illum eum. Et enim vel inventore id omnis. Assumenda et dolorem at. Cumque eos voluptatem ut qui.', b'0', '11.00000', 12, '2018-09-18 01:17:16', '2018-09-18 01:17:16', 'products/default.jpg', 30),
(81, 'Boyer Group', 'Consectetur in commodi omnis a accusantium eum in. Recusandae explicabo velit qui non et nobis ut. Harum ut adipisci omnis harum tempora similique et. Dolor at quia unde voluptatem.', b'1', '38.00000', 3, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 14),
(82, 'Pacocha-Hodkiewicz', 'Voluptatem molestias nobis rerum et autem expedita sint qui. Maiores ad dolore mollitia omnis incidunt quaerat. Impedit ex rerum ut qui ut.', b'0', '33.00000', 6, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 30),
(83, 'McClure-Beahan', 'Harum voluptas voluptas eos ut. Et velit et voluptatem delectus eveniet quis. Facere sit voluptates harum natus molestias unde. Earum culpa est dolores ullam consequuntur dolorem.', b'0', '46.00000', 7, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 25),
(84, 'Maggio, Hammes and Johnston', 'Quo praesentium quia expedita. Dolores illo excepturi autem sint. Provident quia tenetur neque et. Architecto eaque tenetur voluptas eum eligendi facere. Magni possimus ducimus qui qui.', b'1', '57.00000', 10, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 6),
(85, 'Bins Inc', 'Nostrum quidem exercitationem veniam cumque sit. Quidem numquam sed incidunt quo delectus rerum id. Nostrum est reiciendis consequuntur. Voluptas eaque consequatur quo est tenetur.', b'0', '40.00000', 11, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 32),
(86, 'Hauck-Rice', 'Sit blanditiis nisi iste autem omnis dolor. Rem fuga magnam ipsum dolore qui molestiae. Voluptatem reprehenderit qui et. Earum magni quia quia. Ut minima inventore voluptatum aut culpa est.', b'1', '48.00000', 8, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 26),
(87, 'Kerluke Inc', 'Commodi est ea est eligendi. Sed modi assumenda et nam qui natus asperiores. Temporibus quos ipsa voluptatem magnam. Possimus quo consectetur mollitia iusto quod magni.', b'0', '11.00000', 12, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 32),
(88, 'Zulauf-King', 'Nostrum esse aut voluptatem dolorum. Explicabo rerum perferendis quia. Eum consequatur et quam ipsam ut aut. Aliquid sapiente vel voluptatem odio quod suscipit.', b'1', '49.00000', 11, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 33),
(89, 'Howe, Heller and Daugherty', 'Quis molestiae quibusdam et quia laboriosam. Rerum consectetur quia aut non dolor a. Neque et fugiat inventore molestiae.', b'1', '21.00000', 11, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 25),
(90, 'Flatley, Mante and Spinka', 'Tempora ea iure enim sint et. Architecto corrupti ut odio sunt ratione deserunt in. Nemo nemo aut laboriosam odit maxime molestias eius. Vero voluptas deleniti possimus explicabo.', b'1', '22.00000', 3, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 28),
(91, 'Labadie-Beatty', 'Nisi voluptas non ut laboriosam eligendi sapiente nesciunt. Laudantium saepe aliquid amet maxime nostrum doloribus omnis. Et eius ea similique ea.', b'1', '36.00000', 8, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 30),
(92, 'Jenkins, Robel and Bergstrom', 'Voluptas voluptates nisi quaerat et magni sed animi. Autem nostrum error soluta repellat dolorem error neque. Dignissimos eos perferendis cumque doloribus. Rerum est quo quia dolores.', b'0', '27.00000', 11, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 25),
(93, 'VonRueden, Brakus and Ebert', 'In nobis sunt dolor unde ea. Cumque consequuntur rerum et amet quam.', b'1', '14.00000', 8, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 34),
(94, 'Beatty-Parisian', 'Nihil omnis quae illo omnis dolorum rem sit laborum. Nulla saepe non quo nulla laboriosam accusamus sit. Et debitis et dolore nisi atque.', b'1', '15.00000', 12, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 4),
(95, 'Sipes-Robel', 'Sit neque consectetur mollitia ea debitis perspiciatis. Deserunt amet sed reiciendis perspiciatis. Tempore ut non facere rem rerum in.', b'0', '20.00000', 3, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 19),
(96, 'Quigley LLC', 'Earum ad natus quis at illo. Rerum quos sint velit vel error optio. Quae voluptate laborum et unde. Assumenda voluptas error molestias repellendus dolorem.', b'0', '17.00000', 1, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 2),
(97, 'Brakus, Funk and Bogan', 'Qui ipsa et quibusdam necessitatibus itaque repudiandae. Est libero labore dolorem sequi. Eius quae suscipit cupiditate recusandae tempora totam.', b'1', '13.00000', 9, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 16),
(98, 'Mitchell-Bode', 'Commodi rerum quas excepturi. Ut id reiciendis in amet quis cum incidunt. Aut rerum est ipsam voluptas amet consequatur.', b'1', '41.00000', 14, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 21),
(99, 'Price Inc', 'Sunt cupiditate autem eos debitis. Autem consequuntur provident vel aperiam ut harum. Quia animi dolorem temporibus vel. Maiores alias sit reprehenderit.', b'0', '29.00000', 12, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 30),
(100, 'O\'Kon and Sons', 'Inventore veniam id odio non voluptatem quam. Adipisci reprehenderit odio aut harum esse. Et et quo qui. Iusto doloribus repellat nihil voluptatem. Et unde illo nemo fugit aperiam consectetur sint.', b'0', '35.00000', 7, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 26),
(101, 'Kling LLC', 'Aspernatur est ut rem quam. Dolorum sequi pariatur cumque perspiciatis. Nihil occaecati officiis sunt autem autem reprehenderit omnis mollitia.', b'0', '36.00000', 15, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 15),
(102, 'Cummings Inc', 'Reiciendis eius nulla ut sed ea inventore. Consequatur est cumque blanditiis. Autem hic itaque perspiciatis perferendis voluptatem sed ut qui.', b'1', '50.00000', 8, '2018-09-18 01:17:17', '2018-09-18 01:17:17', 'products/default.jpg', 30);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `roles`
--

CREATE TABLE `roles` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `display_name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `roles`
--

INSERT INTO `roles` (`id`, `name`, `display_name`, `created_at`, `updated_at`) VALUES
(1, 'admin', 'Administrator', '2018-09-16 02:43:02', '2018-09-16 02:43:02'),
(2, 'user', 'Normal User', '2018-09-16 02:43:02', '2018-09-16 02:43:02');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `settings`
--

CREATE TABLE `settings` (
  `id` int(10) UNSIGNED NOT NULL,
  `key` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `display_name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` text COLLATE utf8mb4_unicode_ci,
  `details` text COLLATE utf8mb4_unicode_ci,
  `type` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `order` int(11) NOT NULL DEFAULT '1',
  `group` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `settings`
--

INSERT INTO `settings` (`id`, `key`, `display_name`, `value`, `details`, `type`, `order`, `group`) VALUES
(1, 'site.title', 'Site Title', 'Site Title', '', 'text', 1, 'Site'),
(2, 'site.description', 'Site Description', 'Site Description', '', 'text', 2, 'Site'),
(3, 'site.logo', 'Site Logo', '', '', 'image', 3, 'Site'),
(4, 'site.google_analytics_tracking_id', 'Google Analytics Tracking ID', NULL, '', 'text', 4, 'Site'),
(5, 'admin.bg_image', 'Admin Background Image', 'settings\\September2018\\X4EythD0ED8o9AfZyRj6.jpg', '', 'image', 5, 'Admin'),
(6, 'admin.title', 'Admin Title', 'QA Store', '', 'text', 1, 'Admin'),
(7, 'admin.description', 'Admin Description', NULL, '', 'text', 2, 'Admin'),
(8, 'admin.loader', 'Admin Loader', '', '', 'image', 3, 'Admin'),
(9, 'admin.icon_image', 'Admin Icon Image', '', '', 'image', 4, 'Admin'),
(10, 'admin.google_analytics_client_id', 'Google Analytics Client ID (used for admin dashboard)', NULL, '', 'text', 1, 'Admin');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `translations`
--

CREATE TABLE `translations` (
  `id` int(10) UNSIGNED NOT NULL,
  `table_name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `column_name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `foreign_key` int(10) UNSIGNED NOT NULL,
  `locale` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `users`
--

CREATE TABLE `users` (
  `id` int(10) UNSIGNED NOT NULL,
  `role_id` int(10) UNSIGNED DEFAULT NULL,
  `name` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `avatar` varchar(191) COLLATE utf8mb4_unicode_ci DEFAULT 'users/default.png',
  `email_verified_at` timestamp NULL DEFAULT NULL,
  `password` varchar(191) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `settings` text COLLATE utf8mb4_unicode_ci,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `users`
--

INSERT INTO `users` (`id`, `role_id`, `name`, `email`, `avatar`, `email_verified_at`, `password`, `remember_token`, `settings`, `created_at`, `updated_at`) VALUES
(1, 1, 'Carlos Granados', 'cgranados16@gmail.com', 'users/default.png', NULL, '$2y$10$AnQUs7a2YqJR7wzpYmMZ/umJL04Os1AOW6xJCBOMIkm3EVsJWBh9.', 'XsHSMAkA8xQqJWbW1ZlGhi4Rlm2nc9BKT29dMDX3sTlkeUF1fwQyasxdpTQc', NULL, '2018-09-16 02:45:00', '2018-09-16 02:45:00'),
(3, 2, 'galletas', 'galletas@gmail.com', 'users/default.png', NULL, '$2y$10$Wz4BdTj5ZEpOlgmE9TTgiuebTIj7MC.hghqZ3.LoRzknRW4KIiVr6', NULL, NULL, '2018-09-17 02:58:59', '2018-09-17 02:58:59'),
(4, 2, 'galletas', 'galletas2@gmail.com', 'users/default.png', NULL, '$2y$10$vphyLyalPAX9FfXI1t48TuWkD8GVhTZlnymTLmriEmiXiFI1aEquS', NULL, NULL, '2018-09-17 03:08:02', '2018-09-17 03:08:02');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `user_roles`
--

CREATE TABLE `user_roles` (
  `user_id` int(10) UNSIGNED NOT NULL,
  `role_id` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `categories`
--
ALTER TABLE `categories`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `data_rows`
--
ALTER TABLE `data_rows`
  ADD PRIMARY KEY (`id`),
  ADD KEY `data_rows_data_type_id_foreign` (`data_type_id`);

--
-- Indices de la tabla `data_types`
--
ALTER TABLE `data_types`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `data_types_name_unique` (`name`),
  ADD UNIQUE KEY `data_types_slug_unique` (`slug`);

--
-- Indices de la tabla `menus`
--
ALTER TABLE `menus`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `menus_name_unique` (`name`);

--
-- Indices de la tabla `menu_items`
--
ALTER TABLE `menu_items`
  ADD PRIMARY KEY (`id`),
  ADD KEY `menu_items_menu_id_foreign` (`menu_id`);

--
-- Indices de la tabla `migrations`
--
ALTER TABLE `migrations`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `password_resets`
--
ALTER TABLE `password_resets`
  ADD KEY `password_resets_email_index` (`email`);

--
-- Indices de la tabla `permissions`
--
ALTER TABLE `permissions`
  ADD PRIMARY KEY (`id`),
  ADD KEY `permissions_key_index` (`key`);

--
-- Indices de la tabla `permission_role`
--
ALTER TABLE `permission_role`
  ADD PRIMARY KEY (`permission_id`,`role_id`),
  ADD KEY `permission_role_permission_id_index` (`permission_id`),
  ADD KEY `permission_role_role_id_index` (`role_id`);

--
-- Indices de la tabla `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`id`),
  ADD KEY `products_name_index` (`Name`(191)),
  ADD KEY `products_available_index` (`Available`);

--
-- Indices de la tabla `roles`
--
ALTER TABLE `roles`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `roles_name_unique` (`name`);

--
-- Indices de la tabla `settings`
--
ALTER TABLE `settings`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `settings_key_unique` (`key`);

--
-- Indices de la tabla `translations`
--
ALTER TABLE `translations`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `translations_table_name_column_name_foreign_key_locale_unique` (`table_name`,`column_name`,`foreign_key`,`locale`);

--
-- Indices de la tabla `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `users_email_unique` (`email`),
  ADD KEY `users_role_id_foreign` (`role_id`);

--
-- Indices de la tabla `user_roles`
--
ALTER TABLE `user_roles`
  ADD PRIMARY KEY (`user_id`,`role_id`),
  ADD KEY `user_roles_user_id_index` (`user_id`),
  ADD KEY `user_roles_role_id_index` (`role_id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `categories`
--
ALTER TABLE `categories`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=35;

--
-- AUTO_INCREMENT de la tabla `data_rows`
--
ALTER TABLE `data_rows`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- AUTO_INCREMENT de la tabla `data_types`
--
ALTER TABLE `data_types`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT de la tabla `menus`
--
ALTER TABLE `menus`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `menu_items`
--
ALTER TABLE `menu_items`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT de la tabla `migrations`
--
ALTER TABLE `migrations`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT de la tabla `permissions`
--
ALTER TABLE `permissions`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=42;

--
-- AUTO_INCREMENT de la tabla `products`
--
ALTER TABLE `products`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=103;

--
-- AUTO_INCREMENT de la tabla `roles`
--
ALTER TABLE `roles`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT de la tabla `settings`
--
ALTER TABLE `settings`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT de la tabla `translations`
--
ALTER TABLE `translations`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `users`
--
ALTER TABLE `users`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `data_rows`
--
ALTER TABLE `data_rows`
  ADD CONSTRAINT `data_rows_data_type_id_foreign` FOREIGN KEY (`data_type_id`) REFERENCES `data_types` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `menu_items`
--
ALTER TABLE `menu_items`
  ADD CONSTRAINT `menu_items_menu_id_foreign` FOREIGN KEY (`menu_id`) REFERENCES `menus` (`id`) ON DELETE CASCADE;

--
-- Filtros para la tabla `permission_role`
--
ALTER TABLE `permission_role`
  ADD CONSTRAINT `permission_role_permission_id_foreign` FOREIGN KEY (`permission_id`) REFERENCES `permissions` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `permission_role_role_id_foreign` FOREIGN KEY (`role_id`) REFERENCES `roles` (`id`) ON DELETE CASCADE;

--
-- Filtros para la tabla `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `users_role_id_foreign` FOREIGN KEY (`role_id`) REFERENCES `roles` (`id`);

--
-- Filtros para la tabla `user_roles`
--
ALTER TABLE `user_roles`
  ADD CONSTRAINT `user_roles_role_id_foreign` FOREIGN KEY (`role_id`) REFERENCES `roles` (`id`) ON DELETE CASCADE,
  ADD CONSTRAINT `user_roles_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
