#include "user_context.hpp"

namespace kbchad {

	Wpm_Test TSC_to_Wpm_Test(Typing_Session_Context ctx) {
		const float acc = ctx.errors > 0 ? 100.0 - (100.0 * ctx.errors / ctx.text_size) : 100;
		const float wpm = (ctx.words_count * 60000.0 / (ctx.end_time - ctx.start_time)) - ctx.errors;

		return (Wpm_Test){
			.wpm = wpm,
			.acc = acc,
			.errors = ctx.errors,
			.words_count = ctx.words_count,
			.typing_time = ctx.end_time - ctx.start_time
		};
	}

}
